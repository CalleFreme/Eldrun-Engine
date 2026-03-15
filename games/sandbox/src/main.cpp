#include <SDL3/SDL_main.h>

#include "eldrun/core/log.hpp"
#include "eldrun/core/version.hpp"
#include "eldrun/platform/application.hpp"
#include "sandbox_app_state.hpp"

#include <memory>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    eldrun::core::log_info("Starting Eldrun Sandbox...");
    eldrun::core::log_info(eldrun::core::version_string);

    eldrun::platform::Application app(
        {
        .title = "Eldrun Sandbox",
        .width = 1280,
        .height = 720
        },
        std::make_unique<eldrun::sandbox::SandboxAppState>()
    );

    return app.run();
}