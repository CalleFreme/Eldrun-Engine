#pragma once

#include "eldrun/core/timestep.hpp"

namespace eldrun::render
{
    class Renderer;
}

namespace eldrun::runtime
{
    class IAppState
    {
    public:
        virtual ~IAppState() = default;

        virtual void on_enter() {}
        virtual void on_exit() {}

        virtual void update(eldrun::core::Timestep delta_time) = 0;
        virtual void render(eldrun::render::Renderer& renderer) = 0;
    };
}