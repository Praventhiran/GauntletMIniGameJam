#pragma once

#include "Projectile.hpp"


class BoomerangProjectile : public Projectile
{
public:

    BoomerangProjectile(
        Vector2 position,
        Vector2 direction,
        int damage
    );


    void Update(float dt) override;

    void Draw() const override;


    bool CanHitEnemy() const override;

    void OnEnemyHit() override;


    void SetOwnerPosition(Vector2 ownerPosition) override;


private:

    Vector2 m_direction;

    Vector2 m_ownerPosition;


    float m_speed;

    float m_distanceTravelled;

    float m_maxDistance;

    float m_lifetime;


    bool m_returning;

    bool m_canHit;
};