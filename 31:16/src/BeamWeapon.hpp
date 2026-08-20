#pragma once

#include "MeleeWeapon.hpp"

#include "WeaponType.hpp"


class BeamWeapon : public MeleeWeapon
{
public:

    BeamWeapon();


    WeaponType GetType() const override;

    const char* GetDisplayName() const override;

    const char* GetUpgradeName() const override;

    const char* GetUpgradeDescription() const override;


protected:

    void SpawnMeleeAttack(
        Vector2 position,
        Vector2 direction,
        GameContext& context
    ) override;


    void ApplyUpgrade(int newLevel) override;
};