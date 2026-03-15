/*
The Application is the composition root
that owns the render subsystem. App states
must render only through frame-context operations.
*/

#pragma once

#include "eldrun/core/timestep.hpp"
#include "eldrun/runtime/app_state.hpp"
#include "eldrun/render/renderer.hpp"

#include <cstdint>
#include <string>
#include <memory>

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
        // The constructor is marked explicit to prevent implicit conversions from ApplicationConfig to Application,
        // which could lead to unintended behavior if someone accidentally passes an ApplicationConfig where an Application is expected.
        explicit Application(ApplicationConfig config, std::unique_ptr<eldrun::runtime::IAppState> state);
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
        void tick(eldrun::core::Timestep delta_time);
        void render_frame();

        [[nodiscard]] bool should_keep_running() const noexcept; // noexcept makes it clear this function won't throw exceptions

    private:
        ApplicationConfig m_config {};
        std::unique_ptr<eldrun::runtime::IAppState> m_state;
        SDL_Window* m_window { nullptr };
        bool m_is_running { false };
        eldrun::render::Renderer m_renderer {};
    };
}