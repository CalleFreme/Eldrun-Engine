#include "renderer_backend.hpp"

#if defined(ELDRUN_ENABLE_BGFX)

namespace eldrun::render
{
    namespace
    {
        class BgfxRendererBackend final : public IRendererBackend
        {
            // implementation...
        };
    }

    std::unique_ptr<IRendererBackend> create_renderer_backend()
    {
        return std::make_unique<BgfxRendererBackend>();
    }
}

#endif