#include "eldrun/core/log.hpp"
#include "eldrun/core/version.hpp"
#include "eldrun/platform/application.hpp"

int main()
{
    eldrun::core::log_info("Starting Eldrun Sandbox...");
    eldrun::core::log_info(eldrun::core::version_string);

    eldrun::platform::Application app;
    return app.run();
}