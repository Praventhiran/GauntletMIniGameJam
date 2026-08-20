#include "MeleeWeapon.hpp"

#include "raylib.h"

#include <algorithm>
#include <cmath>


namespace
{
    constexpr float MULTI_ATTACK_SPREAD_DEGREES = 10.0f;

    constexpr float MIN_DIRECTION_LENGTH_SQUARED = 0.0001f;
}


MeleeWeapon::MeleeWeapon(WeaponStats stats)
    : Weapon(stats)
{
}


bool MeleeWeapon::RequiresAim() const
{
    return true;
}


void MeleeWeapon::Update(
    float dt,
    Vector2 playerPosition,
    Vector2 mousePosition,
    GameContext& context
)
{
    m_timer += dt;


    if (m_timer < m_stats.cooldown)
    {
        return;
    }


    Vector2 direction =
    {
        mousePosition.x - playerPosition.x,
        mousePosition.y - playerPosition.y
    };


    float lengthSquared =
        direction.x * direction.x +
        direction.y * direction.y;


    if (lengthSquared >
        MIN_DIRECTION_LENGTH_SQUARED)
    {
        float length =
            std::sqrt(lengthSquared);


        direction.x /= length;
        direction.y /= length;
    }
    else
    {
        if (RequiresAim())
        {
            return;
        }


        // Directionless weapons such as AuraWeapon
        // don't care where the mouse is.
        direction =
        {
            1.0f,
            0.0f
        };
    }


    m_timer -= m_stats.cooldown;


    int amount =
        std::max(
            1,
            m_stats.amount
        );


    float center =
        static_cast<float>(amount - 1) /
        2.0f;


    for (int i = 0; i < amount; ++i)
    {
        float angle =
            (
                static_cast<float>(i) -
                center
            ) *
            MULTI_ATTACK_SPREAD_DEGREES *
            DEG2RAD;


        float cosAngle =
            std::cos(angle);


        float sinAngle =
            std::sin(angle);


        Vector2 attackDirection =
        {
            direction.x * cosAngle -
            direction.y * sinAngle,

            direction.x * sinAngle +
            direction.y * cosAngle
        };


        SpawnMeleeAttack(
            playerPosition,
            attackDirection,
            context
        );
    }
}