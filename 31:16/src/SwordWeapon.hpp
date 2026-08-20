#pragma once

#include "MeleeWeapon.hpp"


class SwordWeapon : public MeleeWeapon
{
public:

    SwordWeapon();


protected:

    void SpawnMeleeAttack(
        Vector2 position,
        Vector2 direction,
        GameContext& context
    ) override;
};