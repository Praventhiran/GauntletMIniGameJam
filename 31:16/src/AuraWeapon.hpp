#pragma once

#include "MeleeWeapon.hpp"


class AuraWeapon : public MeleeWeapon
{
public:

    AuraWeapon();


protected:

    void SpawnMeleeAttack(
        Vector2 position,
        Vector2 direction,
        GameContext& context
    ) override;


    bool RequiresAim() const override;
};