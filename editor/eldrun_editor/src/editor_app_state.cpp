#include "eldrun/editor/editor_app_state.hpp"

#include "eldrun/core/log.hpp"
#include "eldrun/render/renderer.hpp"

namespace eldrun::editor
{
	void EditorAppState::on_enter()
	{
		eldrun::core::log_info("EditorAppState entered.");
	}
	void EditorAppState::on_exit()
	{
		eldrun::core::log_info("EditorAppState exited.");
	}
	void EditorAppState::update(eldrun::core::Timestep delta_time)
	{
		m_elapsed_time += delta_time.seconds();
		/* 
		* Update logic for the editor app state goes here. This could include things like:
		* - Handling user input
		* - Updating editor tools and UI
		* - Managing editor-specific game objects or entities
		* - Triggering events related to the editor
		* - Rendering debug information specific to the editor
		* - Other editor-specific logic
		*/
	}
	void EditorAppState::render(eldrun::render::Renderer& renderer)
	{
		/* 
		* Render logic for the editor app state goes here. This could include things like:
		* - Drawing editor-specific game objects or entities
		* - Rendering editor UI elements
		* - Displaying debug information specific to the editor
		* - Other editor-specific rendering
		*/
		// Change the clear color over time to demonstrate that the app state can interact with the renderer.
		eldrun::render::ClearColor color;
		color.r = static_cast<std::uint8_t>((std::sin(m_elapsed_time) + 1.0f) * 127.5f); // Oscillates between 0 and 255 over time.
		color.b = static_cast<std::uint8_t>((std::cos(m_elapsed_time) + 1.0f) * 127.5f); // Oscillates between 0 and 255 over time, but out of phase with red.
		color.g = 128; // Constant green value.
		color.a = 255; // Fully opaque.
		renderer.set_clear_color(color);
	}
}