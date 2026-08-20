#pragma once

#include "ProjectileWeapon.hpp"


class BasicGunWeapon : public ProjectileWeapon
{
public:

    BasicGunWeapon();


protected:

    void SpawnProjectile(
        Vector2 position,
        Vector2 direction,
        GameContext& context
    ) override;
};