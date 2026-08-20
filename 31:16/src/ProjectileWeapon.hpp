#pragma once

#include "Weapon.hpp"


class ProjectileWeapon : public Weapon
{
public:

    explicit ProjectileWeapon(WeaponStats stats);


    void Update(
        float dt,
        Vector2 playerPosition,
        Vector2 mousePosition,
        GameContext& context
    ) override;


protected:

    virtual void SpawnProjectile(
        Vector2 position,
        Vector2 direction,
        GameContext& context
    ) = 0;
};