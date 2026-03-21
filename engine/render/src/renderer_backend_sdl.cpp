#include "renderer_backend.hpp"
#include "eldrun/core/log.hpp"
#include <SDL3/SDL.h>

#if !defined(ELDRUN_ENABLE_BGFX)

namespace eldrun::render
{
    namespace
    {
        class SdlRendererBackend final : public IRendererBackend
        {
        public:
            bool initialize(SDL_Window* window, const RendererConfig&, Viewport) override
            {
                if (m_renderer != nullptr)
                {
                    eldrun::core::log_warning("SDL renderer backend already initialized.");
                    return true;
                }

                if (window == nullptr)
                {
                    eldrun::core::log_error("SDL renderer backend init failed: window was null.");
                    return false;
                }

                m_renderer = SDL_CreateRenderer(window, nullptr);
                if (m_renderer == nullptr)
                {
                    eldrun::core::log_error("SDL_CreateRenderer failed: {}", SDL_GetError());
                    return false;
                }

                eldrun::core::log_info("SDL renderer backend initialized.");
                return true;
            }

            void shutdown() override
            {
                if (m_renderer != nullptr)
                {
                    SDL_DestroyRenderer(m_renderer);
                    m_renderer = nullptr;
                    eldrun::core::log_info("SDL renderer backend shut down.");
                }
            }

            void begin_frame(ClearColor clear_color, Viewport) override
            {
                if (m_renderer == nullptr)
                {
                    return;
                }

                SDL_SetRenderDrawColor(
                    m_renderer,
                    clear_color.r,
                    clear_color.g,
                    clear_color.b,
                    clear_color.a
                );

                SDL_RenderClear(m_renderer);
            }

            void end_frame() override
            {
                if (m_renderer != nullptr)
                {
                    SDL_RenderPresent(m_renderer);
                }
            }

            void set_viewport(Viewport) override
            {
                // No extra work needed for SDL renderer bootstrap path.
            }

            bool is_initialized() const noexcept override
            {
                return m_renderer != nullptr;
            }

        private:
            SDL_Renderer* m_renderer = nullptr;
        };
    }

    std::unique_ptr<IRendererBackend> create_renderer_backend()
    {
        return std::make_unique<SdlRendererBackend>();
    }
}

#endif