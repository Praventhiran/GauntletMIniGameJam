#pragma once

#include "Entity.hpp"


class Projectile : public Entity
{
public:

    Projectile(
        Vector2 position,
        float radius,
        int damage
    );

    virtual ~Projectile() = default;


    int GetDamage() const;


    void Destroy();

    bool IsExpired() const;


    // Can this projectile currently damage an enemy?
    virtual bool CanHitEnemy() const;


    // Each projectile decides what happens after hitting.
    virtual void OnEnemyHit() = 0;


    // Used by projectiles such as boomerangs
    // that need to know where their owner currently is.
    virtual void SetOwnerPosition(Vector2 ownerPosition);


protected:

    int m_damage;

    bool m_destroyed;
};