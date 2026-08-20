#pragma once

#include "WeaponType.hpp"

#include <array>
#include <optional>


class LevelUpMenu
{
public:

    LevelUpMenu();


    void BuildChoices();

    std::optional<WeaponType> Update(float dt);

    void Draw() const;


    void MarkUnlocked(WeaponType type);

    bool HasAvailableWeapons() const;


private:

    bool m_boomerangUnlocked;

    bool m_swordUnlocked;

    bool m_beamUnlocked;

    bool m_auraUnlocked;


    std::array<WeaponType, 3> m_choices;

    std::array<float, 3> m_cardScales;


    int m_choiceCount;

    int m_hoveredIndex;
};