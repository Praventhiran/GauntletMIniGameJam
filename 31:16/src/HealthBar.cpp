#include "HealthBar.hpp"

#include "GameText.hpp"
#include "raylib.h"

#include <algorithm>
#include <cmath>


namespace
{
    constexpr float BAR_X = 30.0f;
    constexpr float BAR_Y = 55.0f;

    constexpr float BAR_WIDTH = 300.0f;
    constexpr float BAR_HEIGHT = 32.0f;

    constexpr float BAR_PADDING = 4.0f;


    constexpr float PUNCH_DURATION = 0.28f;

    constexpr float SHAKE_DURATION = 0.18f;

    constexpr float FLASH_DURATION = 0.12f;
}


HealthBar::HealthBar(int maxHealth)
    : m_maxHealth(maxHealth),
      m_punchTimer(0.0f),
      m_shakeTimer(0.0f),
      m_flashTimer(0.0f)
{
}


void HealthBar::Update(float dt)
{
    if (m_punchTimer > 0.0f)
    {
        m_punchTimer -= dt;

        if (m_punchTimer < 0.0f)
        {
            m_punchTimer = 0.0f;
        }
    }


    if (m_shakeTimer > 0.0f)
    {
        m_shakeTimer -= dt;

        if (m_shakeTimer < 0.0f)
        {
            m_shakeTimer = 0.0f;
        }
    }


    if (m_flashTimer > 0.0f)
    {
        m_flashTimer -= dt;

        if (m_flashTimer < 0.0f)
        {
            m_flashTimer = 0.0f;
        }
    }
}


void HealthBar::OnDamage()
{
    m_punchTimer =
        PUNCH_DURATION;


    m_shakeTimer =
        SHAKE_DURATION;


    m_flashTimer =
        FLASH_DURATION;
}


void HealthBar::Draw(int currentHealth) const
{
    // -------------------------
    // HEALTH
    // -------------------------

    float healthRatio = 0.0f;


    if (m_maxHealth > 0)
    {
        healthRatio =
            static_cast<float>(currentHealth) /
            static_cast<float>(m_maxHealth);
    }


    healthRatio =
        std::clamp(
            healthRatio,
            0.0f,
            1.0f
        );


    // -------------------------
    // PUNCH / BOUNCE
    // -------------------------

    float scaleX = 1.0f;
    float scaleY = 1.0f;


    if (m_punchTimer > 0.0f)
    {
        float progress =
            1.0f -
            (
                m_punchTimer /
                PUNCH_DURATION
            );


        float bounce =
            std::cos(
                progress *
                PI *
                3.0f
            ) *
            (
                1.0f -
                progress
            );


        scaleX -=
            bounce *
            0.05f;


        scaleY +=
            bounce *
            0.14f;
    }


    // -------------------------
    // SHAKE
    // -------------------------

    float shakeX = 0.0f;
    float shakeY = 0.0f;


    if (m_shakeTimer > 0.0f)
    {
        float strength =
            m_shakeTimer /
            SHAKE_DURATION;


        shakeX =
            std::sin(
                m_shakeTimer *
                95.0f
            ) *
            5.0f *
            strength;


        shakeY =
            std::cos(
                m_shakeTimer *
                73.0f
            ) *
            2.0f *
            strength;
    }


    // -------------------------
    // BAR TRANSFORM
    // -------------------------

    float scaledWidth =
        BAR_WIDTH *
        scaleX;


    float scaledHeight =
        BAR_HEIGHT *
        scaleY;


    float barX =
        BAR_X +
        shakeX +
        (
            BAR_WIDTH -
            scaledWidth
        ) /
        2.0f;


    float barY =
        BAR_Y +
        shakeY +
        (
            BAR_HEIGHT -
            scaledHeight
        ) /
        2.0f;


    // -------------------------
    // WHITE BACKGROUND
    // -------------------------

    Rectangle background =
    {
        barX,
        barY,
        scaledWidth,
        scaledHeight
    };


    DrawRectangleRounded(
        background,
        0.25f,
        8,
        WHITE
    );


    // -------------------------
    // RED HP
    // -------------------------

    float innerWidth =
        scaledWidth -
        BAR_PADDING *
        2.0f;


    float innerHeight =
        scaledHeight -
        BAR_PADDING *
        2.0f;


    innerWidth =
        std::max(
            0.0f,
            innerWidth
        );


    innerHeight =
        std::max(
            0.0f,
            innerHeight
        );


    float redWidth =
        innerWidth *
        healthRatio;


    Color healthColor =
        RED;


    if (m_flashTimer > 0.0f)
    {
        healthColor =
        {
            255,
            110,
            110,
            255
        };
    }


    if (redWidth > 0.0f)
    {
        Rectangle healthRectangle =
        {
            barX + BAR_PADDING,
            barY + BAR_PADDING,
            redWidth,
            innerHeight
        };


        DrawRectangleRounded(
            healthRectangle,
            0.25f,
            8,
            healthColor
        );
    }


    // -------------------------
    // HP TEXT
    // -------------------------

    const char* hpText =
        TextFormat(
            "HP %d / %d",
            currentHealth,
            m_maxHealth
        );


    GameText::Draw(
        hpText,
        {
            BAR_X,
            BAR_Y - 28.0f
        },
        20.0f,
        WHITE
    );
}