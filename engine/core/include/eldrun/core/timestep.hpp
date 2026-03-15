#pragma once

namespace eldrun::core
{
    class Timestep
    {
    public:
        constexpr Timestep() = default;
        explicit constexpr Timestep(double seconds)
            : m_seconds(seconds)
        {
        }

        [[nodiscard]] constexpr double seconds() const noexcept
        {
            return m_seconds;
        }

        [[nodiscard]] constexpr double milliseconds() const noexcept
        {
            return m_seconds * 1000.0;
        }

        [[nodiscard]] constexpr float seconds_f() const noexcept
        {
            return static_cast<float>(m_seconds);
        }

    private:
        double m_seconds { 0.0 };
    };
}