#pragma once

#include "MeleeAttack.hpp"


class SwordAttack : public MeleeAttack
{
public:

    SwordAttack(
        Vector2 position,
        Vector2 direction,
        int damage
    );


    void Update(
        float dt,
        Vector2 ownerPosition
    ) override;


    void Draw() const override;


    bool CanDamage() const override;


protected:

    bool CheckCollision(
        const Enemy& enemy
    ) const override;


private:

    Vector2 m_ownerPosition;

    Vector2 m_direction;


    float m_lifetime;
};