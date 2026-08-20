#pragma once

#include "ProjectileWeapon.hpp"


class BasicGunWeapon : public ProjectileWeapon
{
public:

    BasicGunWeapon();


    WeaponType GetType() const override;

    const char* GetDisplayName() const override;

    const char* GetUpgradeName() const override;

    const char* GetUpgradeDescription() const override;


protected:

    void SpawnProjectile(
        Vector2 position,
        Vector2 direction,
        GameContext& context
    ) override;

    void ApplyUpgrade(int newLevel) override;
};