#pragma once

#include "eldrun/runtime/frame_context.hpp"
#include "eldrun/render/renderer.hpp"

/*
* The RenderFrameContext is a specialized frame context for rendering operations.
* It provides an interface for app states to interact with the rendering subsystem
* without directly accessing the Renderer. This ensures that all rendering is
* performed through the frame context, maintaining a clear separation of concerns.
*/

namespace eldrun::render
{
    class RenderFrameContext final : public eldrun::runtime::IFrameContext
    {
    public:
        explicit RenderFrameContext(Renderer& renderer)
            : m_renderer(renderer)
        {
        }

        void set_clear_color(ClearColor color) noexcept
        {
            m_renderer.set_clear_color(color);
		}

        //void set_main_camera(const Camera& camera);
        //void draw_debug_cube(const glm::mat4& transform);
        void draw_debug_grid();


        Renderer& renderer() { return m_renderer; }

    private:
        Renderer& m_renderer;
    };
}