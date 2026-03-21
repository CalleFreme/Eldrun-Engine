#include "eldrun/render/renderer.hpp"
#include "renderer_backend.hpp"
#include "eldrun/core/log.hpp"
#include <memory>
#include <SDL3/SDL.h>

namespace eldrun::render
{
    struct Renderer::Impl
    {
        std::unique_ptr<IRendererBackend> backend;
        ClearColor clear_color{ 30, 34, 42, 255 };
		Viewport viewport {};
	};

    Renderer::Renderer()
        : m_impl(std::make_unique<Impl>())
    {
        m_impl->backend = create_renderer_backend();
	}

    Renderer::~Renderer()
    {
        shutdown();
    }

    Renderer::Renderer(Renderer&& other) noexcept = default;
    Renderer& Renderer::operator=(Renderer&& other) noexcept = default;

    bool Renderer::initialize(SDL_Window* window, const RendererConfig& config)
    {
        m_impl->clear_color = config.clear_color;

        int width = 0;
        int height = 0;
        if (window != nullptr)
        {
            SDL_GetWindowSizeInPixels(window, &width, &height);
            m_impl->viewport.width = static_cast<std::uint32_t>(width);
            m_impl->viewport.height = static_cast<std::uint32_t>(height);
        }

        return m_impl->backend->initialize(window, config, m_impl->viewport);
    }

    void Renderer::shutdown()
    {
        if (m_impl && m_impl->backend)
        {
            m_impl->backend->shutdown();
        }
    }

    void Renderer::begin_frame()
    {
        if (m_impl && m_impl->backend)
        {
            m_impl->backend->begin_frame(m_impl->clear_color, m_impl->viewport);
        }
    }

    void Renderer::end_frame()
    {
        if (m_impl && m_impl->backend)
        {
            m_impl->backend->end_frame();
        }
    }

    bool Renderer::is_initialized() const noexcept
    {
        return m_impl && m_impl->backend && m_impl->backend->is_initialized();
    }

    void Renderer::set_clear_color(ClearColor color) noexcept
    {
        m_impl->clear_color = color;
    }

    ClearColor Renderer::clear_color() const noexcept
    {
        return m_impl->clear_color;
    }

	void Renderer::set_viewport(Viewport viewport) noexcept
    {
        m_impl->viewport = viewport;
        if (m_impl && m_impl->backend)
        {
            m_impl->backend->set_viewport(viewport);
        }
	}

    Viewport Renderer::viewport() const noexcept
    {
        return m_impl->viewport;
    }
}