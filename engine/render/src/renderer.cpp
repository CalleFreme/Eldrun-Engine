#include "eldrun/render/renderer.hpp"

#include "eldrun/core/log.hpp"

#include <SDL3/SDL.h>

namespace eldrun::render
{
    Renderer::~Renderer()
    {
        shutdown();
    }

    Renderer::Renderer(Renderer&& other) noexcept
        : m_renderer(other.m_renderer)
        , m_clear_color(other.m_clear_color)
    {
        other.m_renderer = nullptr;
    }

    Renderer& Renderer::operator=(Renderer&& other) noexcept
    {
        if (this != &other)
        {
            shutdown();

            m_renderer = other.m_renderer;
            m_clear_color = other.m_clear_color;

            other.m_renderer = nullptr;
        }

        return *this;
    }

    bool Renderer::initialize(SDL_Window* window, const RendererConfig& config)
    {
        if (m_renderer != nullptr)
        {
            eldrun::core::log_warning("Renderer already initialized.");
            return true;
        }

        if (window == nullptr)
        {
            eldrun::core::log_error("Renderer initialization failed: window was null.");
            return false;
        }

        m_renderer = SDL_CreateRenderer(window, nullptr);
        if (m_renderer == nullptr)
        {
            eldrun::core::log_error("SDL_CreateRenderer failed: {}", SDL_GetError());
            return false;
        }

        m_clear_color = config.clear_color;

        eldrun::core::log_info("Renderer initialized successfully.");
        return true;
    }

    void Renderer::shutdown()
    {
        if (m_renderer != nullptr)
        {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr;
            eldrun::core::log_info("Renderer shut down.");
        }
    }

    void Renderer::begin_frame()
    {
        if (m_renderer == nullptr)
        {
            return;
        }

        SDL_SetRenderDrawColor(
            m_renderer,
            m_clear_color.r,
            m_clear_color.g,
            m_clear_color.b,
            m_clear_color.a
        );

        SDL_RenderClear(m_renderer);
    }

    void Renderer::end_frame()
    {
        if (m_renderer == nullptr)
        {
            return;
        }

        SDL_RenderPresent(m_renderer);
    }

    bool Renderer::is_initialized() const noexcept
    {
        return m_renderer != nullptr;
    }

    void Renderer::set_clear_color(ClearColor color) noexcept
    {
        m_clear_color = color;
    }
}