#pragma once

#include "LevelUpOption.hpp"

#include <array>
#include <optional>


class Player;


class LevelUpMenu
{
public:

    LevelUpMenu();


    void BuildChoices(const Player& player);

    std::optional<LevelUpOption> Update(float dt);

    void Draw(const Player& player) const;


    bool HasAvailableOptions(const Player& player) const;


private:

    std::array<LevelUpOption, 3> m_choices;

    std::array<float, 3> m_cardScales;


    int m_choiceCount;

    int m_hoveredIndex;
};