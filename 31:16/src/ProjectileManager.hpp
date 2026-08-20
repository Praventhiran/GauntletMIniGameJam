#pragma once

#include "raylib.h"
#include "Enemy.hpp"
#include "Projectile.hpp"

#include <memory>
#include <vector>


class ProjectileManager
{
public:

    void SpawnBullet(
        Vector2 position,
        Vector2 direction,
        int damage,
        float speed
    );


    void SpawnBoomerang(
        Vector2 position,
        Vector2 direction,
        int damage
    );


    void Update(
        float dt,
        std::vector<std::unique_ptr<Enemy>>& enemies,
        Vector2 playerPosition
    );


    void Draw() const;


private:

    std::vector<std::unique_ptr<Projectile>>
        m_projectiles;
};