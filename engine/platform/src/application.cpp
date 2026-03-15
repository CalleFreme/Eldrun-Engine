#include "eldrun/platform/application.hpp"

#include "eldrun/core/log.hpp"
#include "eldrun/render/render_frame_context.hpp"

#include <SDL3/SDL.h>

#include <utility>

namespace eldrun::platform
{
    namespace
    {
        // Needed for converting SDL_GetTicksNS() result to seconds in the main loop.
        constexpr std::uint64_t nanoseconds_per_second = 1'000'000'000ull;
    }

    Application::Application(ApplicationConfig config, std::unique_ptr<eldrun::runtime::IAppState> state)
        : m_config(std::move(config)), m_state(std::move(state)) // Application should take ownership of the config and state
    {
    }

    Application::~Application()
    {
        shutdown();
    }
    
    int Application::run()
    {
        if (!initialize())
        {
            eldrun::core::log_error("Application initialization failed.");
            return 1;
        }

        std::uint64_t previous_counter = SDL_GetTicksNS(); // Get the initial timestamp for the main loop

        while (should_keep_running())
        {
            const std::uint64_t current_counter = SDL_GetTicksNS();
            const double delta_seconds =
                static_cast<double>(current_counter - previous_counter) /
                static_cast<double>(nanoseconds_per_second);

            previous_counter = current_counter;

            process_events();
            tick(eldrun::core::Timestep(delta_seconds));
            render_frame();
        }

        return 0;
    }

    bool Application::initialize()
    {
        if (m_state == nullptr)
        {
            eldrun::core::log_error("Application initialization failed: no app state was provided.");
            return false;
        }

        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            eldrun::core::log_error("SDL_Init failed: {}", SDL_GetError());
            return false;
        }

        m_window = SDL_CreateWindow(
            m_config.title.c_str(),
            m_config.width,
            m_config.height,
            SDL_WINDOW_RESIZABLE
        );

        if (m_window == nullptr)
        {
            eldrun::core::log_error("SDL_CreateWindow failed: {}", SDL_GetError());
            SDL_Quit();
            return false;
        }

        eldrun::core::log_info(
            "Window created: '{}' ({}x{})",
            m_config.title,
            m_config.width,
            m_config.height
        );

        eldrun::render::RendererConfig renderer_config {};
        renderer_config.clear_color = { 30, 34, 42, 255 }; // A dark gray-blue color

        if (!m_renderer.initialize(m_window, renderer_config))
        {
            eldrun::core::log_error("Renderer initialization failed.");
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
            SDL_Quit();
            return false;
        }

        m_state->on_enter(); // on_enter tells the app state that we're starting the application, so it can perform any necessary setup.

        m_is_running = true;

        eldrun::core::log_info(
            "Application initialized: '{}' ({}x{})",
            m_config.title,
            m_config.width,
            m_config.height
        );

        return true;
    }

    void Application::shutdown()
    {
        if (m_state != nullptr)
        {
            m_state->on_exit(); // on_exit tells the app state that we're shutting down the application, so it can perform any necessary cleanup.
        }

        m_renderer.shutdown();

        if (m_window != nullptr)
        {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }

        if (SDL_WasInit(SDL_INIT_VIDEO))
        {
            SDL_Quit();
        }

        m_is_running = false;
    }

    void Application::process_events()
    {
        SDL_Event event {};
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                m_is_running = false;
                break;

            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_ESCAPE)
                {
                    m_is_running = false;
                }
                break;

            default:
                break;
            }
        }
    }

    void Application::tick(eldrun::core::Timestep delta_time)
    {
        if (m_state != nullptr)
        {
            m_state->update(delta_time);
        }
    }

    void Application::render_frame()
    {
        m_renderer.begin_frame();

        if (m_state != nullptr)
        {
			eldrun::render::RenderFrameContext frame_context(m_renderer);
            m_state->render(frame_context);
        }
        
        m_renderer.end_frame();
    }

    bool Application::should_keep_running() const noexcept
    {
        return m_is_running;
    }
}