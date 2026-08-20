#pragma once

#include "raylib.h"

#include "WeaponStats.hpp"
#include "WeaponType.hpp"


struct GameContext;


class Weapon
{
public:

    explicit Weapon(WeaponStats stats);

    virtual ~Weapon() = default;


    virtual void Update(
        float dt,
        Vector2 playerPosition,
        Vector2 mousePosition,
        GameContext& context
    ) = 0;


    virtual WeaponType GetType() const = 0;

    virtual const char* GetDisplayName() const = 0;

    virtual const char* GetUpgradeName() const = 0;

    virtual const char* GetUpgradeDescription() const = 0;


    int GetLevel() const;

    bool CanUpgrade() const;

    void Upgrade();


protected:

    virtual void ApplyUpgrade(int newLevel) = 0;


    WeaponStats m_stats;

    float m_timer;

    int m_level;


private:

    static constexpr int MAX_LEVEL = 5;
};