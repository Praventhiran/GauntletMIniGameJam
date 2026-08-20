#pragma once

#include "MeleeWeapon.hpp"


class BeamWeapon : public MeleeWeapon
{
public:

    BeamWeapon();


protected:

    void SpawnMeleeAttack(
        Vector2 position,
        Vector2 direction,
        GameContext& context
    ) override;
};