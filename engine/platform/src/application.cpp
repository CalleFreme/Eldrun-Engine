#include "eldrun/platform/application.hpp"

#include "eldrun/core/log.hpp"

#include <SDL3/SDL.h>

namespace eldrun::platform
{
    int Application::run()
    {
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            eldrun::core::log_error(SDL_GetError());
            return 1;
        }

        eldrun::core::log_info("SDL initialized.");

        SDL_Window* window = SDL_CreateWindow(
            "Eldrun Sandbox",
            1280,
            720,
            SDL_WINDOW_RESIZABLE
        );

        if (window == nullptr)
        {
            eldrun::core::log_error(SDL_GetError());
            SDL_Quit();
            return 1;
        }

        eldrun::core::log_info("Window created.");

        bool running = true;

        while (running)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;

                case SDL_EVENT_KEY_DOWN:
                    if (event.key.key == SDLK_ESCAPE)
                    {
                        running = false;
                    }
                    break;

                default:
                    break;
                }
            }

            SDL_Delay(1);
        }

        SDL_DestroyWindow(window);
        eldrun::core::log_info("Window destroyed.");

        SDL_Quit();
        eldrun::core::log_info("SDL shutdown complete.");

        return 0;
    }
}