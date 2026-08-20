#include "ExperienceBar.hpp"

#include "GameText.hpp"
#include "raylib.h"

#include <algorithm>
#include <cmath>


namespace
{
    constexpr float BAR_WIDTH = 520.0f;

    constexpr float BAR_HEIGHT = 22.0f;

    constexpr float BAR_Y = 20.0f;

    constexpr float BAR_PADDING = 3.0f;


    constexpr float XP_PUNCH_DURATION =
        0.18f;


    constexpr float LEVEL_UP_DURATION =
        0.60f;
}


ExperienceBar::ExperienceBar()
    : m_xpPunchTimer(0.0f),
      m_levelUpTimer(0.0f)
{
}


void ExperienceBar::Update(float dt)
{
    if (m_xpPunchTimer > 0.0f)
    {
        m_xpPunchTimer -= dt;


        if (m_xpPunchTimer < 0.0f)
        {
            m_xpPunchTimer = 0.0f;
        }
    }


    if (m_levelUpTimer > 0.0f)
    {
        m_levelUpTimer -= dt;


        if (m_levelUpTimer < 0.0f)
        {
            m_levelUpTimer = 0.0f;
        }
    }
}


void ExperienceBar::OnXPCollected()
{
    m_xpPunchTimer =
        XP_PUNCH_DURATION;
}


void ExperienceBar::OnLevelUp()
{
    m_levelUpTimer =
        LEVEL_UP_DURATION;
}


void ExperienceBar::Draw(
    int level,
    int currentXP,
    int requiredXP
) const
{
    // -------------------------
    // XP RATIO
    // -------------------------

    float xpRatio = 0.0f;


    if (requiredXP > 0)
    {
        xpRatio =
            static_cast<float>(currentXP) /
            static_cast<float>(requiredXP);
    }


    xpRatio =
        std::clamp(
            xpRatio,
            0.0f,
            1.0f
        );


    // -------------------------
    // BAR POSITION
    // -------------------------

    float barX =
        (
            static_cast<float>(
                GetScreenWidth()
            ) -
            BAR_WIDTH
        ) /
        2.0f;


    // -------------------------
    // XP PICKUP PUNCH
    // -------------------------

    float scaleX = 1.0f;

    float scaleY = 1.0f;


    if (m_xpPunchTimer > 0.0f)
    {
        float progress =
            1.0f -
            (
                m_xpPunchTimer /
                XP_PUNCH_DURATION
            );


        float punch =
            std::sin(
                progress *
                PI
            ) *
            (
                1.0f -
                progress
            );


        scaleX +=
            punch *
            0.015f;


        scaleY +=
            punch *
            0.22f;
    }


    // -------------------------
    // LEVEL-UP PUNCH
    // -------------------------

    if (m_levelUpTimer > 0.0f)
    {
        float progress =
            1.0f -
            (
                m_levelUpTimer /
                LEVEL_UP_DURATION
            );


        float punch =
            std::sin(
                progress *
                PI *
                2.0f
            ) *
            (
                1.0f -
                progress
            );


        scaleY +=
            std::fabs(punch) *
            0.35f;
    }


    // -------------------------
    // SCALE AROUND CENTER
    // -------------------------

    float scaledWidth =
        BAR_WIDTH *
        scaleX;


    float scaledHeight =
        BAR_HEIGHT *
        scaleY;


    float drawX =
        barX +
        (
            BAR_WIDTH -
            scaledWidth
        ) /
        2.0f;


    float drawY =
        BAR_Y +
        (
            BAR_HEIGHT -
            scaledHeight
        ) /
        2.0f;


    // -------------------------
    // LEVEL-UP GLOW
    // -------------------------

    if (m_levelUpTimer > 0.0f)
    {
        float strength =
            m_levelUpTimer /
            LEVEL_UP_DURATION;


        Rectangle glow =
        {
            drawX - 5.0f,
            drawY - 5.0f,
            scaledWidth + 10.0f,
            scaledHeight + 10.0f
        };


        DrawRectangleRounded(
            glow,
            0.35f,
            8,
            Fade(
                YELLOW,
                0.35f *
                strength
            )
        );
    }


    // -------------------------
    // WHITE BACKGROUND
    // -------------------------

    Rectangle background =
    {
        drawX,
        drawY,
        scaledWidth,
        scaledHeight
    };


    DrawRectangleRounded(
        background,
        0.35f,
        8,
        WHITE
    );


    // -------------------------
    // XP FILL
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
            innerWidth,
            0.0f
        );


    innerHeight =
        std::max(
            innerHeight,
            0.0f
        );


    float fillWidth =
        innerWidth *
        xpRatio;


    Color fillColor =
        GOLD;


    if (m_levelUpTimer > 0.0f)
    {
        fillColor =
            YELLOW;
    }


    if (fillWidth > 0.0f)
    {
        Rectangle fill =
        {
            drawX + BAR_PADDING,
            drawY + BAR_PADDING,
            fillWidth,
            innerHeight
        };


        DrawRectangleRounded(
            fill,
            0.35f,
            8,
            fillColor
        );
    }


    // -------------------------
    // LEVEL TEXT
    // -------------------------

    const char* levelText =
        TextFormat(
            "LV. %d",
            level
        );


    Vector2 levelSize =
        GameText::Measure(
            levelText,
            18.0f
        );


    GameText::Draw(
        levelText,
        {
            drawX -
                levelSize.x -
                15.0f,

            BAR_Y +
                BAR_HEIGHT /
                2.0f -
                levelSize.y /
                2.0f
        },
        18.0f,
        WHITE
    );


    // -------------------------
    // XP NUMBER
    // -------------------------

    const char* xpText =
        TextFormat(
            "%d / %d",
            currentXP,
            requiredXP
        );


    Vector2 xpSize =
        GameText::Measure(
            xpText,
            14.0f
        );


    GameText::Draw(
        xpText,
        {
            barX +
                BAR_WIDTH /
                2.0f -
                xpSize.x /
                2.0f,

            BAR_Y +
                BAR_HEIGHT /
                2.0f -
                xpSize.y /
                2.0f
        },
        14.0f,
        BLACK
    );
}