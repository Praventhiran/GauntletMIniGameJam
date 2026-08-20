#include "XPOrb.hpp"

#include "raylib.h"

#include <cmath>


namespace
{
    constexpr float XP_ORB_RADIUS = 7.0f;

    constexpr float PULSE_SPEED = 5.0f;

    constexpr float PULSE_AMOUNT = 1.5f;
}


XPOrb::XPOrb(Vector2 position,int value)
    : Entity(position,XP_ORB_RADIUS),
      m_value(value),
      m_elapsedTime(0.0f)
{
}


void XPOrb::Update(float dt)
{
    m_elapsedTime += dt;
}


void XPOrb::Draw() const
{
    float pulse =
        std::sin(
            m_elapsedTime *
            PULSE_SPEED
        );


    float radius =
        m_radius +
        pulse *
        PULSE_AMOUNT;


    // Small outer glow.
    DrawCircleV(
        m_position,
        radius + 4.0f,
        Fade(
            SKYBLUE,
            0.25f
        )
    );


    // Main XP orb.
    DrawCircleV(
        m_position,
        radius,
        SKYBLUE
    );


    // Bright center.
    DrawCircleV(
        m_position,
        radius * 0.45f,
        WHITE
    );
}


int XPOrb::GetValue() const
{
    return m_value;
}