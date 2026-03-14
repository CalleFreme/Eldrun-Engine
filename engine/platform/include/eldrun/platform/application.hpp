/*
Initialize SDL
Create a window
Run a while-loop
poll events
quit on window close or Escape
shut SDL down cleanly

Application class will likely be split into:
- app config
- window wrapper
- input state
- time/frame management
- main loop hooks
*/

#pragma once

#include "eldrun/render/renderer.hpp"

#include <cstdint>
#include <string>

struct SDL_Window;

namespace eldrun::platform
{
    struct ApplicationConfig
    {
        std::string title { "Eldrun" };
        std::int32_t width { 1280 };
        std::int32_t height { 720 };
    };

    class Application
    {
    public:
        explicit Application(ApplicationConfig config = {});
        ~Application();

        // Non-copyable
        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        // Non-movable
        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;

        int run();
    
    private:
        bool initialize();
        void shutdown();

        void process_events();
        void tick(double delta_seconds);
        void render_frame();

        [[nodiscard]] bool should_keep_running() const noexcept; // noexcept makes it clear this function won't throw exceptions

    private:
        ApplicationConfig m_config {};
        SDL_Window* m_window { nullptr };
        bool m_is_running { false };
        eldrun::render::Renderer m_renderer {};
    };
}