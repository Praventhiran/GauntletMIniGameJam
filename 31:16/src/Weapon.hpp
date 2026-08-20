#pragma once

#include "raylib.h"
#include "WeaponStats.hpp"


struct GameContext;


class Weapon
{
public:

    explicit Weapon(
        WeaponStats stats
    );


    virtual ~Weapon() = default;


    virtual void Update(
        float dt,
        Vector2 playerPosition,
        Vector2 mousePosition,
        GameContext& context
    ) = 0;


protected:

    WeaponStats m_stats;

    float m_timer;
};