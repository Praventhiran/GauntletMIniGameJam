#include "LevelUpMenu.hpp"

#include "GameAudio.hpp"
#include "GameText.hpp"

#include "raylib.h"

#include <algorithm>
#include <vector>


namespace
{
    constexpr float CARD_WIDTH = 290.0f;
    constexpr float CARD_HEIGHT = 260.0f;

    constexpr float CARD_GAP = 25.0f;

    constexpr float CARD_Y = 245.0f;


    constexpr float NORMAL_SCALE = 1.0f;

    constexpr float HOVER_SCALE = 1.06f;

    constexpr float HOVER_SPEED = 12.0f;


    struct WeaponCardData
    {
        WeaponType type;

        const char* name;

        const char* descriptionLine1;

        const char* descriptionLine2;
    };


    constexpr WeaponCardData WEAPON_DATA[] =
    {
        {
            WeaponType::Boomerang,
            "BOOMERANG",
            "Flies outward",
            "then returns"
        },

        {
            WeaponType::Sword,
            "SWORD",
            "Fast close-range",
            "directional slash"
        },

        {
            WeaponType::Beam,
            "BEAM",
            "Charge and fire",
            "a huge beam"
        },

        {
            WeaponType::Aura,
            "AURA",
            "Damage enemies",
            "around the player"
        }
    };


    const WeaponCardData& GetWeaponData(WeaponType type)
    {
        for (const WeaponCardData& data : WEAPON_DATA)
        {
            if (data.type == type)
            {
                return data;
            }
        }

        return WEAPON_DATA[0];
    }


    Rectangle GetBaseCardRectangle(int index, int cardCount)
    {
        float totalWidth =
            CARD_WIDTH * static_cast<float>(cardCount) +
            CARD_GAP * static_cast<float>(cardCount - 1);


        float startX =
            (
                static_cast<float>(GetScreenWidth()) -
                totalWidth
            ) /
            2.0f;


        return
        {
            startX + static_cast<float>(index) * (CARD_WIDTH + CARD_GAP),
            CARD_Y,
            CARD_WIDTH,
            CARD_HEIGHT
        };
    }


    Rectangle ScaleRectangle(Rectangle rectangle, float scale)
    {
        float scaledWidth = rectangle.width * scale;

        float scaledHeight = rectangle.height * scale;


        return
        {
            rectangle.x + (rectangle.width - scaledWidth) / 2.0f,
            rectangle.y + (rectangle.height - scaledHeight) / 2.0f,
            scaledWidth,
            scaledHeight
        };
    }
}


LevelUpMenu::LevelUpMenu()
    : m_boomerangUnlocked(false),
      m_swordUnlocked(false),
      m_beamUnlocked(false),
      m_auraUnlocked(false),
      m_choices {},
      m_cardScales
      {
          NORMAL_SCALE,
          NORMAL_SCALE,
          NORMAL_SCALE
      },
      m_choiceCount(0),
      m_hoveredIndex(-1)
{
}


void LevelUpMenu::BuildChoices()
{
    std::vector<WeaponType> availableWeapons;


    if (!m_boomerangUnlocked)
    {
        availableWeapons.push_back(WeaponType::Boomerang);
    }


    if (!m_swordUnlocked)
    {
        availableWeapons.push_back(WeaponType::Sword);
    }


    if (!m_beamUnlocked)
    {
        availableWeapons.push_back(WeaponType::Beam);
    }


    if (!m_auraUnlocked)
    {
        availableWeapons.push_back(WeaponType::Aura);
    }


    // -------------------------
    // RANDOMISE
    // -------------------------

    for (int i = static_cast<int>(availableWeapons.size()) - 1; i > 0; i--)
    {
        int randomIndex = GetRandomValue(0, i);

        std::swap(
            availableWeapons[static_cast<std::size_t>(i)],
            availableWeapons[static_cast<std::size_t>(randomIndex)]
        );
    }


    // -------------------------
    // MAXIMUM 3 OPTIONS
    // -------------------------

    m_choiceCount = std::min(3, static_cast<int>(availableWeapons.size()));


    for (int i = 0; i < m_choiceCount; i++)
    {
        m_choices[static_cast<std::size_t>(i)] = availableWeapons[static_cast<std::size_t>(i)];

        m_cardScales[static_cast<std::size_t>(i)] = NORMAL_SCALE;
    }


    m_hoveredIndex = -1;
}


std::optional<WeaponType> LevelUpMenu::Update(float dt)
{
    Vector2 mousePosition = GetMousePosition();


    // -------------------------
    // KEYBOARD
    // -------------------------

    if (m_choiceCount >= 1 && IsKeyPressed(KEY_ONE))
    {
        return m_choices[0];
    }


    if (m_choiceCount >= 2 && IsKeyPressed(KEY_TWO))
    {
        return m_choices[1];
    }


    if (m_choiceCount >= 3 && IsKeyPressed(KEY_THREE))
    {
        return m_choices[2];
    }


    // -------------------------
    // FIND HOVERED CARD
    // -------------------------

    int newHoveredIndex = -1;


    for (int i = 0; i < m_choiceCount; i++)
    {
        Rectangle cardRectangle = GetBaseCardRectangle(i, m_choiceCount);


        if (CheckCollisionPointRec(mousePosition, cardRectangle))
        {
            newHoveredIndex = i;

            break;
        }
    }


    // -------------------------
    // HOVER ENTER SOUND
    // -------------------------

    if (newHoveredIndex != m_hoveredIndex)
    {
        if (newHoveredIndex >= 0)
        {
            GameAudio::PlayMenuScroll();
        }

        m_hoveredIndex = newHoveredIndex;
    }


    // -------------------------
    // CARD SCALE
    // -------------------------

    for (int i = 0; i < m_choiceCount; i++)
    {
        bool hovered = i == m_hoveredIndex;

        float targetScale = hovered ? HOVER_SCALE : NORMAL_SCALE;

        float& currentScale = m_cardScales[static_cast<std::size_t>(i)];

        float interpolation = std::min(1.0f, HOVER_SPEED * dt);

        currentScale += (targetScale - currentScale) * interpolation;
    }


    // -------------------------
    // MOUSE SELECT
    // -------------------------

    if (m_hoveredIndex >= 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return m_choices[static_cast<std::size_t>(m_hoveredIndex)];
    }


    return std::nullopt;
}


void LevelUpMenu::Draw() const
{
    // -------------------------
    // TITLE
    // -------------------------

    const char* title = "LEVEL UP!";

    Vector2 titleSize = GameText::Measure(title, 54.0f);


    GameText::Draw(
        title,
        {
            static_cast<float>(GetScreenWidth()) / 2.0f - titleSize.x / 2.0f,
            100.0f
        },
        54.0f,
        YELLOW
    );


    // -------------------------
    // SUBTITLE
    // -------------------------

    const char* subtitle = "CHOOSE A WEAPON";

    Vector2 subtitleSize = GameText::Measure(subtitle, 20.0f);


    GameText::Draw(
        subtitle,
        {
            static_cast<float>(GetScreenWidth()) / 2.0f - subtitleSize.x / 2.0f,
            172.0f
        },
        20.0f,
        WHITE
    );


    // -------------------------
    // CARDS
    // -------------------------

    for (int i = 0; i < m_choiceCount; i++)
    {
        WeaponType type = m_choices[static_cast<std::size_t>(i)];

        const WeaponCardData& data = GetWeaponData(type);


        Rectangle baseRectangle = GetBaseCardRectangle(i, m_choiceCount);

        Rectangle cardRectangle = ScaleRectangle(
            baseRectangle,
            m_cardScales[static_cast<std::size_t>(i)]
        );


        bool hovered = i == m_hoveredIndex;


        // -------------------------
        // SHADOW
        // -------------------------

        Rectangle shadow =
        {
            cardRectangle.x + 8.0f,
            cardRectangle.y + 10.0f,
            cardRectangle.width,
            cardRectangle.height
        };


        DrawRectangleRounded(
            shadow,
            0.12f,
            8,
            Fade(BLACK, 0.45f)
        );


        // -------------------------
        // BORDER
        // -------------------------

        Rectangle border =
        {
            cardRectangle.x - 4.0f,
            cardRectangle.y - 4.0f,
            cardRectangle.width + 8.0f,
            cardRectangle.height + 8.0f
        };


        DrawRectangleRounded(
            border,
            0.12f,
            8,
            hovered ? YELLOW : WHITE
        );


        // -------------------------
        // CARD
        // -------------------------

        Color cardColor = Color{55, 55, 70, 255};


        if (hovered)
        {
            cardColor = Color{75, 75, 95, 255};
        }


        DrawRectangleRounded(
            cardRectangle,
            0.12f,
            8,
            cardColor
        );


        // -------------------------
        // NUMBER
        // -------------------------

        const char* numberText = TextFormat("%d", i + 1);


        GameText::Draw(
            numberText,
            {
                cardRectangle.x + 18.0f,
                cardRectangle.y + 15.0f
            },
            18.0f,
            hovered ? YELLOW : LIGHTGRAY
        );


        // -------------------------
        // NAME
        // -------------------------

        Vector2 nameSize = GameText::Measure(data.name, 26.0f);


        GameText::Draw(
            data.name,
            {
                cardRectangle.x + cardRectangle.width / 2.0f - nameSize.x / 2.0f,
                cardRectangle.y + 60.0f
            },
            26.0f,
            hovered ? YELLOW : WHITE
        );


        // -------------------------
        // DESCRIPTION
        // -------------------------

        Vector2 lineOneSize = GameText::Measure(data.descriptionLine1, 16.0f);


        GameText::Draw(
            data.descriptionLine1,
            {
                cardRectangle.x + cardRectangle.width / 2.0f - lineOneSize.x / 2.0f,
                cardRectangle.y + 125.0f
            },
            16.0f,
            LIGHTGRAY
        );


        Vector2 lineTwoSize = GameText::Measure(data.descriptionLine2, 16.0f);


        GameText::Draw(
            data.descriptionLine2,
            {
                cardRectangle.x + cardRectangle.width / 2.0f - lineTwoSize.x / 2.0f,
                cardRectangle.y + 152.0f
            },
            16.0f,
            LIGHTGRAY
        );


        // -------------------------
        // SELECT
        // -------------------------

        const char* selectText = hovered ? "SELECT!" : "UNLOCK";

        Vector2 selectSize = GameText::Measure(selectText, 18.0f);


        GameText::Draw(
            selectText,
            {
                cardRectangle.x + cardRectangle.width / 2.0f - selectSize.x / 2.0f,
                cardRectangle.y + 210.0f
            },
            18.0f,
            YELLOW
        );
    }
}


void LevelUpMenu::MarkUnlocked(WeaponType type)
{
    switch (type)
    {
        case WeaponType::Boomerang:
            m_boomerangUnlocked = true;
            break;

        case WeaponType::Sword:
            m_swordUnlocked = true;
            break;

        case WeaponType::Beam:
            m_beamUnlocked = true;
            break;

        case WeaponType::Aura:
            m_auraUnlocked = true;
            break;

        case WeaponType::BasicGun:
            break;
    }
}


bool LevelUpMenu::HasAvailableWeapons() const
{
    return
        !m_boomerangUnlocked ||
        !m_swordUnlocked ||
        !m_beamUnlocked ||
        !m_auraUnlocked;
}