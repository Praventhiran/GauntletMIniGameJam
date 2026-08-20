#pragma once

#include "MeleeAttack.hpp"


class AuraAttack : public MeleeAttack
{
public:

    AuraAttack(
        Vector2 position,
        int damage
    );


    void Update(
        float dt,
        Vector2 ownerPosition
    ) override;


    void Draw() const override;


    bool CanDamage() const override;


    void ApplySecondaryEffect(
        Enemy& enemy
    ) override;


    void FinishFrame() override;


protected:

    bool CheckCollision(
        const Enemy& enemy
    ) const override;


private:

    Vector2 m_ownerPosition;


    float m_elapsedTime;

    float m_damageTimer;


    bool m_damageTickThisFrame;

    bool m_knockbackTriggered;

    bool m_knockbackThisFrame;
};