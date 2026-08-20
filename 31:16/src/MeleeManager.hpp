#pragma once

#include "raylib.h"

#include "Enemy.hpp"
#include "MeleeAttack.hpp"

#include <memory>
#include <vector>


class MeleeManager
{
public:

    void SpawnSword(
        Vector2 position,
        Vector2 direction,
        int damage
    );


    void SpawnBeam(
        Vector2 position,
        Vector2 direction,
        int damage
    );

    void SpawnAura(
        Vector2 position,
        int damage
    );


    void Update(
        float dt,
        std::vector<std::unique_ptr<Enemy>>& enemies,
        Vector2 playerPosition
    );


    void Draw() const;


private:

    std::vector<std::unique_ptr<MeleeAttack>>
        m_attacks;
};