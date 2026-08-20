#include "LevelUpMenu.hpp"

#include "GameAudio.hpp"
#include "GameText.hpp"
#include "Player.hpp"

#include "raylib.h"

#include <algorithm>
#include <array>
#include <vector>


namespace
{

constexpr float CARD_WIDTH = 300.0f;
constexpr float CARD_HEIGHT = 350.0f;

constexpr float CARD_GAP = 25.0f;

constexpr float CARD_Y = 220.0f;


constexpr float NORMAL_SCALE = 1.0f;

constexpr float HOVER_SCALE = 1.10f;

constexpr float HOVER_SPEED = 12.0f;



constexpr std::array<WeaponType, 5> ALL_WEAPONS =
{
    WeaponType::BasicGun,
    WeaponType::Boomerang,
    WeaponType::Sword,
    WeaponType::Beam,
    WeaponType::Aura
};



const char* GetWeaponName(WeaponType type)
{
    switch(type)
    {
        case WeaponType::BasicGun:
            return "FIREWORK LAUNCHER";

        case WeaponType::Boomerang:
            return "ROTI CANAI";

        case WeaponType::Sword:
            return "JALUR GEMILANG";

        case WeaponType::Beam:
            return "TEH TARIK BEAM";

        case WeaponType::Aura:
            return "DURIAN SMELL";
    }


    return "WEAPON";
}



const char* GetUnlockDescription(WeaponType type)
{
    switch(type)
    {
        case WeaponType::BasicGun:
            return "Explosive fireworks\nrain from the sky.";

        case WeaponType::Boomerang:
            return "Roticanai spins\nand comes back.";

        case WeaponType::Sword:
            return "Malaysia flag\nbecomes a blade.";

        case WeaponType::Beam:
            return "Hot teh tarik\nmelts enemies.";

        case WeaponType::Aura:
            return "Deadly durian aura\nhurts enemies.";
    }


    return "";
}



Rectangle GetBaseCardRectangle(
    int index,
    int cardCount
)
{
    float totalWidth =
        CARD_WIDTH *
        static_cast<float>(cardCount)
        +
        CARD_GAP *
        static_cast<float>(cardCount - 1);



    float startX =
        (
            static_cast<float>(GetScreenWidth())
            -
            totalWidth
        )
        /
        2.0f;



    return
    {
        startX +
        static_cast<float>(index)
        *
        (
            CARD_WIDTH +
            CARD_GAP
        ),

        CARD_Y,

        CARD_WIDTH,

        CARD_HEIGHT
    };
}



Rectangle ScaleRectangle(
    Rectangle rectangle,
    float scale
)
{
    float newWidth =
        rectangle.width * scale;


    float newHeight =
        rectangle.height * scale;



    return
    {
        rectangle.x +
        (rectangle.width - newWidth)
        /
        2.0f,

        rectangle.y +
        (rectangle.height - newHeight)
        /
        2.0f,

        newWidth,

        newHeight
    };
}

}



// ------------------------------------------------------
// Constructor
// ------------------------------------------------------

LevelUpMenu::LevelUpMenu()

    :

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



// ------------------------------------------------------
// Build Choices
// ------------------------------------------------------

void LevelUpMenu::BuildChoices(
    const Player& player
)
{
    std::vector<LevelUpOption> availableOptions;



    for(auto type : ALL_WEAPONS)
    {

        if(player.HasWeapon(type))
        {

            if(player.CanUpgradeWeapon(type))
            {
                availableOptions.push_back(
                {
                    type,
                    LevelUpOptionKind::Upgrade,
                    player.GetWeaponLevel(type)+1
                });
            }

        }

        else if(type != WeaponType::BasicGun)
        {

            availableOptions.push_back(
            {
                type,
                LevelUpOptionKind::Unlock,
                1
            });

        }

    }



    for(
        int i =
        static_cast<int>(availableOptions.size()) - 1;

        i > 0;

        i--
    )
    {

        int randomIndex =
            GetRandomValue(0,i);


        std::swap(
            availableOptions[i],
            availableOptions[randomIndex]
        );

    }



    m_choiceCount =
        std::min(
            3,
            static_cast<int>(
                availableOptions.size()
            )
        );



    for(int i=0;i<m_choiceCount;i++)
    {

        m_choices[i] =
            availableOptions[i];


        m_cardScales[i] =
            NORMAL_SCALE;

    }



    m_hoveredIndex=-1;
}



// ------------------------------------------------------
// Update
// ------------------------------------------------------

std::optional<LevelUpOption>
LevelUpMenu::Update(float dt)
{

    Vector2 mouse =
        GetMousePosition();



    if(m_choiceCount >=1 &&
       IsKeyPressed(KEY_ONE))
    {
        return m_choices[0];
    }


    if(m_choiceCount >=2 &&
       IsKeyPressed(KEY_TWO))
    {
        return m_choices[1];
    }


    if(m_choiceCount >=3 &&
       IsKeyPressed(KEY_THREE))
    {
        return m_choices[2];
    }



    int hovered=-1;



    for(int i=0;i<m_choiceCount;i++)
    {

        if(CheckCollisionPointRec(
            mouse,
            GetBaseCardRectangle(
                i,
                m_choiceCount
            )))
        {

            hovered=i;
            break;

        }

    }



    if(hovered != m_hoveredIndex)
    {

        if(hovered>=0)
        {
            GameAudio::PlayMenuScroll();
        }


        m_hoveredIndex=hovered;

    }



    for(int i=0;i<m_choiceCount;i++)
    {

        bool selected =
            i==m_hoveredIndex;


        float target =
            selected
            ?
            HOVER_SCALE
            :
            NORMAL_SCALE;



        m_cardScales[i]
            +=
            (
                target -
                m_cardScales[i]
            )
            *
            std::min(
                1.0f,
                HOVER_SPEED*dt
            );

    }



    if(
        m_hoveredIndex>=0 &&
        IsMouseButtonPressed(
            MOUSE_BUTTON_LEFT
        )
    )
    {
        return m_choices[m_hoveredIndex];
    }



    return std::nullopt;
}




// ------------------------------------------------------
// Draw
// ------------------------------------------------------

void LevelUpMenu::Draw(
    const Player& player
) const
{


    const char* title =
        "LEVEL UP!";


    Vector2 titleSize =
        GameText::Measure(
            title,
            54
        );



    GameText::Draw(
        title,
        {
            GetScreenWidth()/2.0f
            -
            titleSize.x/2.0f,

            70
        },

        54,

        YELLOW
    );



    const char* subtitle =
        "CHOOSE YOUR POWER";



    Vector2 subtitleSize =
        GameText::Measure(
            subtitle,
            20
        );



    GameText::Draw(
        subtitle,
        {
            GetScreenWidth()/2.0f
            -
            subtitleSize.x/2.0f,

            145
        },

        20,

        WHITE
    );





    for(int i=0;i<m_choiceCount;i++)
    {


        auto option =
            m_choices[i];



        Rectangle card =
            ScaleRectangle(
                GetBaseCardRectangle(
                    i,
                    m_choiceCount
                ),

                m_cardScales[i]
            );



        bool hovered =
            i==m_hoveredIndex;



        DrawRectangleRounded(
            {
                card.x+8,
                card.y+10,
                card.width,
                card.height
            },

            0.12f,
            8,

            Fade(
                BLACK,
                0.45f
            )
        );



        DrawRectangleRounded(
            {
                card.x-4,
                card.y-4,
                card.width+8,
                card.height+8
            },

            0.12f,
            8,

            hovered
            ?
            YELLOW
            :
            WHITE
        );



        DrawRectangleRounded(
            card,

            0.12f,

            8,

            hovered
            ?
            Color{75,75,95,255}
            :
            Color{55,55,70,255}
        );



        // NUMBER

        GameText::Draw(
            TextFormat(
                "%d",
                i+1
            ),

            {
                card.x+20,
                card.y+18
            },

            18,

            LIGHTGRAY
        );



        // WEAPON NAME

        const char* weapon =
            GetWeaponName(
                option.type
            );


        Vector2 weaponSize =
            GameText::Measure(
                weapon,
                24
            );



        GameText::Draw(
            weapon,

            {
                card.x+
                card.width/2
                -
                weaponSize.x/2,

                card.y+65
            },

            24,

            hovered
            ?
            YELLOW
            :
            WHITE
        );



        // LEVEL

        const char* level =
            option.kind ==
            LevelUpOptionKind::Unlock

            ?

            "NEW WEAPON"

            :

            TextFormat(
                "LEVEL %d",
                option.targetLevel
            );



        Vector2 levelSize =
            GameText::Measure(
                level,
                18
            );


        GameText::Draw(
            level,

            {
                card.x+
                card.width/2
                -
                levelSize.x/2,

                card.y+115
            },

            18,

            option.kind ==
            LevelUpOptionKind::Unlock
            ?
            GREEN
            :
            SKYBLUE
        );



        // UPGRADE NAME


        const char* upgrade =
            option.kind ==
            LevelUpOptionKind::Unlock

            ?

            "UNLOCK"

            :

            player.GetWeaponUpgradeName(
                option.type
            );



        Vector2 upgradeSize =
            GameText::Measure(
                upgrade,
                20
            );



        GameText::Draw(
            upgrade,

            {
                card.x+
                card.width/2
                -
                upgradeSize.x/2,

                card.y+165
            },

            20,

            YELLOW
        );



        // DESCRIPTION


        const char* desc =
            option.kind ==
            LevelUpOptionKind::Unlock

            ?

            GetUnlockDescription(
                option.type
            )

            :

            player.GetWeaponUpgradeDescription(
                option.type
            );



        GameText::Draw(
            desc,

            {
                card.x+35,
                card.y+220
            },

            16,

            LIGHTGRAY
        );



        // ACTION


        const char* action =
            option.kind ==
            LevelUpOptionKind::Unlock

            ?

            "PRESS TO UNLOCK"

            :

            "PRESS TO UPGRADE";



        Vector2 actionSize =
            GameText::Measure(
                action,
                16
            );



        GameText::Draw(
            action,

            {
                card.x+
                card.width/2
                -
                actionSize.x/2,

                card.y+305
            },

            16,

            YELLOW
        );


    }

}




bool LevelUpMenu::HasAvailableOptions(
    const Player& player
) const
{

    for(auto type : ALL_WEAPONS)
    {

        if(player.HasWeapon(type))
        {

            if(player.CanUpgradeWeapon(type))
                return true;

        }

        else if(type != WeaponType::BasicGun)
        {
            return true;
        }

    }


    return false;
}