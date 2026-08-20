#pragma once

#include "ProjectileWeapon.hpp"


class BoomerangWeapon : public ProjectileWeapon
{
public:

    BoomerangWeapon();


protected:

    void SpawnProjectile(
        Vector2 position,
        Vector2 direction,
        GameContext& context
    ) override;
};