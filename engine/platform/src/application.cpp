#include "eldrun/platform/application.hpp"

#include "eldrun/core/log.hpp"

#include <SDL3/SDL.h>

namespace eldrun::platform
{
    int Application::run()
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Eldrun", "Application::run() entered.", nullptr);

        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), nullptr);
            eldrun::core::log_error(SDL_GetError());
            return 1;
        }

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Eldrun", "SDL initialized.", nullptr);

        SDL_Window* window = SDL_CreateWindow(
            "Eldrun Sandbox",
            1280,
            720,
            SDL_WINDOW_RESIZABLE
        );

        if (window == nullptr)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), nullptr);
            eldrun::core::log_error(SDL_GetError());
            SDL_Quit();
            return 1;
        }

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Eldrun", "Window created.", window);

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
        SDL_Quit();
        return 0;
    }
}