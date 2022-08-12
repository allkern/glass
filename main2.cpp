#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#include "SDL.h"

#define SDL_SHADER_GL_STANDALONE
#include "SDL_shader.h"

#include "SDL_keycode.h"

//#include "opencv2/opencv.hpp"

#define LOG_TARGET_LINUX
#include "log.hpp"

#include <chrono>

SDL_Window* window = nullptr;

bool shader_stack_available = true;

SDL_Shader* encoder = nullptr,
            * decoder = nullptr,
            * process = nullptr,
            * adjust = nullptr;

#include <iostream>
#include <array>
#include <vector>

enum input_class_t {
    IC_IMAGE,
    IC_VIDEO
};

enum input_type_t {
    IT_PNG,
    IT_JPG,
    IT_MP4
};

input_type_t get_input_type(std::string filename) {
    auto p = filename.find_last_of('.');

    std::string ext = filename.substr(p + 1);

    if (ext == "jpg" ) return IT_JPG;
    if (ext == "jpeg") return IT_JPG;
    if (ext == "png" ) return IT_PNG;
    if (ext == "mp4" ) return IT_MP4;
}

input_class_t get_input_class(input_type_t it) {
    switch (it) {
        case IT_JPG:
        case IT_PNG:
            return IC_IMAGE;
        case IT_MP4:
            return IC_VIDEO;
    }

    return IC_IMAGE;
}

std::array <std::vector <uint32_t>, 5> buffers;

struct hms_t {
    unsigned hours, minutes, seconds;
};

hms_t get_hms_from_seconds(unsigned seconds) {
    unsigned s = seconds % 60;
    unsigned m = int(std::floor(seconds / 60)) % 60;
    unsigned h = int(std::floor(m / 60));

    return { h, m, s };
}

#undef main

int get_gl_format(int channels) {
    switch (channels) {
        case 3: return 0x1907;
        case 4: return 0x1908;
    }
}

bool load_shaders(int width, int height, int bpp) {
    SDL_Init(SDL_INIT_EVERYTHING);

    int format = get_gl_format(bpp);

    encoder = SDL_CreateShader(window, "shaders/identity.vert", "shaders/encode.frag");
    if (!encoder) { _log(warning, "Shader compilation error:\n%s", SDL_GetError()); shader_stack_available = false; goto unavailable; }
    decoder = SDL_CreateShader(window, "shaders/identity.vert", "shaders/decode.frag");
    if (!decoder) { _log(warning, "Shader compilation error:\n%s", SDL_GetError()); shader_stack_available = false; goto unavailable; }
    process = SDL_CreateShader(window, "shaders/identity.vert", "shaders/process.frag");
    if (!process) { _log(warning, "Shader compilation error:\n%s", SDL_GetError()); shader_stack_available = false; goto unavailable; }
    adjust  = SDL_CreateShader(window, "shaders/identity.vert", "shaders/adjust.frag");
    if (!adjust ) { _log(warning, "Shader compilation error:\n%s", SDL_GetError()); shader_stack_available = false; goto unavailable; }

    unavailable:
    if (!shader_stack_available) {
        _log(warning, "Shader stack unavailable, continuing with default rendering");

        return false;
    }
    return true;
}

int main(int argc, const char* argv[]) {
    _log::init("ntscly");

    input_type_t it = get_input_type(std::string(argv[1]));
    input_class_t ic = get_input_class(it);

    if (ic == IC_IMAGE) {
        // Load image
        int width, height, bpp;

        unsigned char* data = stbi_load(argv[1], &width, &height, &bpp, 0);

        if (!data) {
            _log(debug, "Couldn't load image \"%s\"", argv[1]);

            return 0;
        }

        int gl_format = get_gl_format(bpp);

        _log(ok, "Loaded image \"%s\"", argv[1]);
        _log(info, "Size: %ux%u\n\t    Format: %ubpp", width, height, bpp);

        _log(info, "Loading shaders...");

        window = SDL_CreateWindow(
            "dummy",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height,
            SDL_WINDOW_OPENGL
        );

        SDL_GL_CreateContext(window);

        if (!load_shaders(width, height, bpp)) return 0;

        std::vector <uint32_t> scaled;

        double scale = 1.0;

        if (argv[2]) {
            scale = std::stod(argv[2]);

            int pw = width, ph = height;

            width = std::round((double)width * scale);
            height = std::round((double)height * scale);

            scaled.resize(width * height);

            unsigned char* ptr = reinterpret_cast<unsigned char*>(scaled.data());

            stbir_resize_uint8(data, pw, ph, pw * bpp, ptr, width, height, width * bpp, bpp);

            _log(info, "Resized image by a factor of %f (%ux%u)", scale, width, height);
        }

        for (std::vector <uint32_t>& b : buffers)
            b.resize(width * height);

        SDL_ShaderBindRawTexture(adjust, reinterpret_cast<uint32_t*>(data), width, height);
        SDL_ShaderBindRawTexture(encoder, buffers[0].data(), width, height);
        SDL_ShaderBindRawTexture(decoder, buffers[1].data(), width, height);
        SDL_ShaderBindRawTexture(process, buffers[2].data(), width, height);
        
        if (!SDL_CreateShaderFramebuffer(encoder)) { _log(debug, "encoder: %s", SDL_GetError()); }
        if (!SDL_CreateShaderFramebuffer(decoder)) { _log(debug, "decoder: %s", SDL_GetError()); }
        if (!SDL_CreateShaderFramebuffer(process)) { _log(debug, "decoder: %s", SDL_GetError()); }
        if (!SDL_CreateShaderFramebuffer(adjust )) { _log(debug, "hermite: %s", SDL_GetError()); }

        _log(info, "Processing image...");

        bool open = true;

        while (open) {
            // SDL_UseShaderWithFramebuffer(adjust, buffers[0].data());
            // SDL_UseShaderWithFramebuffer(encoder, buffers[1].data());
            // SDL_UseShaderWithFramebuffer(decoder, buffers[2].data());
            SDL_UseShader(process, reinterpret_cast<uint32_t*>(data));

            SDL_GL_SwapWindow(window);

            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT: { open = false; }
                }
            }
        }

        _log(info, "Writing to output...");
        stbi_write_png("image.png", width, height, bpp, buffers[3].data(), width * bpp);
    }
    /* else {
        cv::VideoCapture video(argv[1]);

        if (!video.isOpened()) {
            _log(debug, "Couldn't open video file");

            return 0;
        }

        cv::Mat frame;

        video >> frame;

        if (frame.empty()) {
            _log(info, "Video is empty! I have nothing to do here!");

            return 0;
        }

        unsigned width, height, channels, length, fps;

        width = frame.cols;
        height = frame.rows;
        channels = frame.channels();
        fps = video.get(cv::CAP_PROP_FPS);
        length = video.get(cv::CAP_PROP_FRAME_COUNT);
        int format = get_gl_format(channels);

        _log(ok, "Loaded video \"%s\"", argv[1]);
        _log(info, "Size: %ux%ux%u@%u\n\t    Format: %u channels", width, height, length, fps, channels);

        _log(debug, "Loading shaders...");

        if (!load_shaders(width, height, channels)) return 0;

        for (std::vector <uint32_t>& b : buffers)
            b.resize(width * height);
        
        //unsigned char* cvt = new unsigned char[frame.total() * 4];
        //uint32_t* cvt_ptr = reinterpret_cast<uint32_t*>(cvt);

        //cv::Mat rgba_mat(frame.size(), CV_8UC4, cvt);

        cv::VideoWriter output("output.mp4", cv::VideoWriter::fourcc('m','p','4','v'), fps, cv::Size(width, height));
        cv::Mat output_mat(width, height, CV_8UC4);

        _log(info, "Rendering...");

        auto start = std::chrono::high_resolution_clock::now();
        auto end = start;
        
        unsigned frames = 0, seconds = 0, remaining = length;

        while (!frame.empty()) {
            if (std::chrono::duration_cast<std::chrono::seconds>(end - start).count() == 1) {
                start = std::chrono::high_resolution_clock::now();
                end = start;
                seconds++;

                hms_t hms = get_hms_from_seconds(seconds);

                int remaining_seconds = remaining / frames;
                hms_t remaining_hms = get_hms_from_seconds(remaining_seconds);

                double speed = ((double)frames) / ((double)fps);

                _log(debug, "Elapsed: %02u:%02u:%02u, ETA: %02u:%02u:%02u (%u), Speed: %4.fx",
                    hms.hours, hms.minutes, hms.seconds,
                    remaining_hms.hours, remaining_hms.minutes, remaining_hms.seconds,
                    remaining,
                    speed
                );

                frames = 0;
            } else {
                end = std::chrono::high_resolution_clock::now();
            }
            // Convert frame from 3 channel format to 4 channel
            //cv::cvtColor(frame, rgba_mat, cv::COLOR_BGR2RGBA, 4);
            //_log(debug, "cvt[0]=%08x, cvt[1]=%08x, cvt[2]=%08x", cvt_ptr[0], cvt_ptr[1], cvt_ptr[2]);

            SDL_ShaderBindRawTexture(encoder, reinterpret_cast<uint32_t*>(frame.data), width, height);
            SDL_ShaderBindRawTexture(decoder, buffers[0].data(), width, height);
            SDL_ShaderBindRawTexture(hermite, buffers[1].data(), width, height);
            SDL_ShaderBindRawTexture(process, buffers[2].data(), width, height);
            SDL_ShaderBindRawTexture(curvature, buffers[3].data(), width, height);

            SDL_UseShaderWithFramebuffer(encoder, buffers[0].data());
            SDL_UseShaderWithFramebuffer(decoder, buffers[1].data());
            SDL_UseShaderWithFramebuffer(hermite, buffers[2].data());
            SDL_UseShaderWithFramebuffer(process, buffers[3].data());

            std::memcpy(output_mat.data, buffers[3].data(), width * height * channels);

            output.write(output_mat);

            frames++;
            remaining--;

            video >> frame;
        }

        _log(debug, "Reached end of stream, finalizing...");
        output.release();
	    video.release();
    }*/

    SDL_DestroyWindow(window);
    SDL_Quit();

    _log(ok, "Done!");
}