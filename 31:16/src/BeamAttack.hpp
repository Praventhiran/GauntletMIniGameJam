#pragma once

#include "MeleeAttack.hpp"


class BeamAttack : public MeleeAttack
{
public:

    BeamAttack(
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

    float GetBeamLength() const;


    Vector2 m_ownerPosition;

    Vector2 m_direction;


    float m_elapsedTime;

    float m_opacity;


    bool m_damageActive;
};