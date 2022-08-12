// This is a CLI tool that reads an (optionally scaled) image, passes
// it through some shaders and writes the output to a new image named "image.png".

// Using Glass' simple API without an OpenGL loader

#include "glass.hpp"

#include "SDL2/SDL.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#undef main

int main(int argc, const char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    int width, height, bpp;

    unsigned char* data = stbi_load(argv[1], &width, &height, &bpp, 4);

    uint32_t* ptr = (uint32_t*)data;

    if (!data) {
        _log(debug, "Couldn't load image \"%s\"", argv[1]);

        return 0;
    }

    _log::init("filter_image");

    _log(ok, "Loaded image \"%s\"", argv[1]);
    _log(info, "Format: %ux%ux%ubpp", width, height, bpp);

    float scale = 1.0f;

    if (argv[2]) {
        scale = std::stof(argv[2]);
    }

    SDL_Window* window = SDL_CreateWindow(
        "dummy",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width * scale, height * scale,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    // This isn't really needed
    // SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

    // Create OpenGL context
    SDL_GL_CreateContext(window);

    // Load OpenGL functions (using SDL's loader)
    glass::init(SDL_GL_GetProcAddress);

    glass::set_output_size(width, height, scale);

    glass::push_shader("shaders/adjust.frag");
    glass::push_shader("shaders/vcr.frag");
    glass::push_shader("shaders/encode.frag");
    glass::push_shader("shaders/decode.frag");
    glass::push_shader("shaders/process.frag");
    glass::push_shader("shaders/adjust.frag");
    //glass::push_shader("shaders/adjust.frag");

    uint32_t* output = new uint32_t[int((width * scale) * (height * scale))];

    glass::set_input((uint32_t*)data, width, height);

    bool open = true;

    int x = 0, y = 0;

    while (open) {
        SDL_GetMouseState(&x, &y);

        glass::update_mouse(x, y);
        glass::render();

        SDL_GL_SwapWindow(window);

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: { open = false; } break;
            }
        }
    }

    glass::set_output(output);

    glass::render();

    _log(info, "Writing to output...");

    stbi_write_png("image.png", width * scale, height * scale, 4, output, width * scale * 4);

    _log(ok, "Done!");

    return 0;
}