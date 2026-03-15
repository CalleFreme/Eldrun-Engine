#pragma once

#include <cstdint>

struct SDL_Window;

namespace eldrun::render
{
    struct ClearColor
    {
        std::uint8_t r { 0 };
        std::uint8_t g { 0 };
        std::uint8_t b { 0 };
        std::uint8_t a { 255 };
    };

    struct RendererConfig
    {
		ClearColor clear_color{ 30, 34, 42, 255 };
		bool enable_vsync = true;
    };

    struct Viewport
    {
        std::uint32_t width = 0;
		std::uint32_t height = 0;
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

        bool is_initialized() const noexcept;

        void set_clear_color(ClearColor color) noexcept;
        [[nodiscard]] ClearColor clear_color() const noexcept;

		void set_viewport(Viewport viewport) noexcept;
		[[nodiscard]] Viewport viewport() const noexcept;

    private:
        struct Impl;
		std::unique_ptr<Impl> m_impl; // Private implementation pointer
    };
}