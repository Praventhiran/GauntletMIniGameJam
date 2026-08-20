#pragma once

#include "Projectile.hpp"


class BulletProjectile : public Projectile
{
public:

    BulletProjectile(
        Vector2 position,
        Vector2 direction,
        int damage,
        float speed
    );


    void Update(float dt) override;

    void Draw() const override;


    void OnEnemyHit() override;


private:

    Vector2 m_direction;

    float m_speed;

    float m_lifetime;
};