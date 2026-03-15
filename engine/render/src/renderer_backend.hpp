#pragma once

#include "eldrun/render/renderer.hpp"
#include <memory>

struct SDL_Window;

namespace eldrun::render
{
	class IRendererBackend
	{
	public:
		virtual ~IRendererBackend() = default;

		virtual bool initialize(SDL_Window* window, const RendererConfig& config, Viewport viewport) = 0;
		virtual void shutdown() = 0;

		virtual void begin_frame(ClearColor clear_color, Viewport viewport) = 0;
		virtual void end_frame() = 0;

		virtual void set_viewport(Viewport viewport) = 0;
		virtual bool is_initialized() const noexcept = 0;

	};
	std::unique_ptr<IRendererBackend> create_renderer_backend();
}