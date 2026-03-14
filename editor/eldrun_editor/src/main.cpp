#include <SDL3/SDL_main.h>

#include "eldrun/core/log.hpp"
#include "eldrun/platform/application.hpp"

int main()
{
    eldrun::core::log_info("Starting Eldrun Editor...");

    eldrun::platform::Application app;
    return app.run();
}