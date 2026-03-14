#pragma once

#include <cstdint>

struct SDL_Window;
struct SDL_Renderer;

namespace eldrun::render
{
    struct ClearColor
    {
        std::uint8_t r { 26 };
        std::uint8_t g { 26 };
        std::uint8_t b { 32 };
        std::uint8_t a { 255 };
    };

    struct RendererConfig
    {
        ClearColor clear_color {};
    };

    class Renderer
    {
    public:
        Renderer() = default;
        ~Renderer();

        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;

        Renderer(Renderer&& other) noexcept;
        Renderer& operator=(Renderer&& other) noexcept;

        bool initialize(SDL_Window* window, const RendererConfig& config = {});
        void shutdown();

        void begin_frame();
        void end_frame();

        [[nodiscard]] bool is_initialized() const noexcept;

        void set_clear_color(ClearColor color) noexcept;

    private:
        SDL_Renderer* m_renderer { nullptr };
        ClearColor m_clear_color {};
    };
}