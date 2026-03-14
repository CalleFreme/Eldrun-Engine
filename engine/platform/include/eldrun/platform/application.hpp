/*
Initialize SDL
Create a window
Run a while-loop
poll events
quit on window close or Escape
shut SDL down cleanly

Application class will likely be split into:
- app config
- window wrapper
- input state
- time/frame management
- main loop hooks
*/

#pragma once

namespace eldrun::platform
{
    class Application
    {
    public:
        Application() = default;
        ~Application() = default;

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        int run();
    };
}