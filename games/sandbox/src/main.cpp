#include <SDL3/SDL_main.h>

#include "eldrun/core/log.hpp"
#include "eldrun/core/version.hpp"
#include "eldrun/platform/application.hpp"

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    eldrun::core::log_info("Starting Eldrun Sandbox...");
    eldrun::core::log_info(eldrun::core::version_string);

    eldrun::platform::Application app;
    return app.run();
}