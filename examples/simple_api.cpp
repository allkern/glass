// Example app using Glass' Simple API
// without an OpenGL loader.

#include "glass.hpp"

#include "SDL2/SDL.h"

#undef main

#define WIDTH 800
#define HEIGHT 600
#define SCALE 1

uint32_t buf[WIDTH * HEIGHT * SCALE];
uint32_t output[WIDTH * HEIGHT * SCALE];

int main(int argc, const char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_Window* window = SDL_CreateWindow(
        "TV capture",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HEIGHT,
        SDL_WINDOW_OPENGL
    );

    // This isn't really needed
    // SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

    SDL_GL_CreateContext(window);

    // Load OpenGL functions (using SDL's loader)
    glass::init(SDL_GL_GetProcAddress);

    glass::set_output_size(WIDTH, HEIGHT);

    glass::push_shader("shaders/smpte.frag");
    glass::push_shader("shaders/vcr.frag");
    glass::push_shader("shaders/encode.frag");
    glass::push_shader("shaders/decode.frag");
    glass::push_shader("shaders/process.frag");

    bool open = true;

    // Mouse coords
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

    return 0;
}