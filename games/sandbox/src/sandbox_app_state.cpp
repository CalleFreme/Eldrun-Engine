#include "sandbox_app_state.hpp"

#include "eldrun/core/log.hpp"
#include "eldrun/render/render_frame_context.hpp"

/*
* Purpose of this app state:
* - Provide a simple sandbox environment for testing and experimenting with new features, mechanics, or rendering techniques without affecting the main game. An integration playground.
* - This app state can be used to quickly iterate on ideas, debug specific systems, or demonstrate features in isolation.
* - It can be switched to from the main menu or other parts of the game, allowing developers to easily access it for testing purposes.
* - The sandbox app state can be used to create small test scenes, render debug information, or run experiments with game mechanics without the overhead of the full game context.
* - It serves as a flexible and isolated environment for development and testing, helping to speed up the iteration process and improve the overall quality of the game.
* - In the future, we can expand the sandbox app state to include features like:
*  - A simple UI for spawning game objects or triggering events
* - Tools for visualizing physics simulations or AI behavior
* - A console for executing commands or running scripts
* - Other features that would be useful for development and testing without affecting the main game experience.
*/
namespace eldrun::sandbox
{
    void SandboxAppState::on_enter()
    {
        eldrun::core::log_info("SandboxAppState entered.");
    }

    void SandboxAppState::on_exit()
    {
        eldrun::core::log_info("SandboxAppState exited.");
    }

    void SandboxAppState::update(eldrun::core::Timestep delta_time)
    {
        m_elapsed_time += delta_time.seconds();
        /* 
		* Update logic for the sandbox app state goes here. This could include things like:
        * - Handling user input
        * - Updating game objects
        * - Managing physics simulations
        * - Triggering events
        * - Rendering debug information
        * - Other game-specific logic
        */
    }

    void SandboxAppState::render(eldrun::runtime::IFrameContext& frame)
    {
        auto& render_frame = static_cast<eldrun::render::RenderFrameContext&>(frame);

		eldrun::render::ClearColor color;
		color.r = static_cast<std::uint8_t>((std::sin(m_elapsed_time) + 1.0f) * 127.5f); // Oscillates between 0 and 255 over time.
		color.g = static_cast<std::uint8_t>((std::cos(m_elapsed_time) + 1.0f) * 127.5f); // Oscillates between 0 and 255 over time, but out of phase with red.
		color.b = 128; // Constant blue value.
		color.a = 255; // Fully opaque.

		render_frame.set_clear_color(color);
    }
}