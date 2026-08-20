#pragma once

#include "raylib.h"

#include <unordered_set>


class Enemy;


class MeleeAttack
{
public:

    explicit MeleeAttack(int damage);

    virtual ~MeleeAttack() = default;


    virtual void Update(
        float dt,
        Vector2 ownerPosition
    ) = 0;


    virtual void Draw() const = 0;


    virtual bool CanDamage() const = 0;


    bool TryHitEnemy(Enemy& enemy);


    // Optional additional effects.
    virtual void ApplySecondaryEffect(
        Enemy& enemy
    );


    // Called after all enemies have been processed
    // for this frame.
    virtual void FinishFrame();


    bool IsExpired() const;


protected:

    virtual bool CheckCollision(
        const Enemy& enemy
    ) const = 0;


    void Destroy();


    int m_damage;

    bool m_expired;


    std::unordered_set<const Enemy*>
        m_hitEnemies;
};