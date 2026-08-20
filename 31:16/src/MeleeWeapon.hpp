#pragma once

#include "Weapon.hpp"


class MeleeWeapon : public Weapon
{
public:

    explicit MeleeWeapon(WeaponStats stats);


    void Update(
        float dt,
        Vector2 playerPosition,
        Vector2 mousePosition,
        GameContext& context
    ) override;


protected:

    virtual void SpawnMeleeAttack(
        Vector2 position,
        Vector2 direction,
        GameContext& context
    ) = 0;


    virtual bool RequiresAim() const;
};