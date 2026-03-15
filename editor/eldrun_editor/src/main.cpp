#include <SDL3/SDL_main.h>

#include "eldrun/core/log.hpp"
#include "eldrun/platform/application.hpp"
#include "eldrun/editor/editor_app_state.hpp"

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    eldrun::core::log_info("Starting Eldrun Editor...");

    eldrun::platform::Application app(
        {
        .title = "Eldrun Editor",
        .width = 1600,
        .height = 900
        },
		std::make_unique<eldrun::editor::EditorAppState>()
    );

    return app.run();
}