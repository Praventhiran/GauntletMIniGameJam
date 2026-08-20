#pragma once

#include "WeaponType.hpp"


enum class LevelUpOptionKind
{
    Unlock,
    Upgrade
};


struct LevelUpOption
{
    WeaponType type;

    LevelUpOptionKind kind;

    int targetLevel;
};