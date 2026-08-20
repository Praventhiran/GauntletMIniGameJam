#include "PlayerProgress.hpp"


namespace
{
    constexpr int BASE_XP_REQUIREMENT = 50;

    constexpr int XP_INCREASE_PER_LEVEL = 25;
}


PlayerProgress::PlayerProgress()
    : m_level(1),
      m_currentXP(0),
      m_xpToNextLevel(
          CalculateRequiredXP(1)
      )
{
}


int PlayerProgress::AddXP(int amount)
{
    if (amount <= 0)
    {
        return 0;
    }


    m_currentXP += amount;


    int levelsGained = 0;


    while (
        m_currentXP >=
        m_xpToNextLevel
    )
    {
        m_currentXP -=
            m_xpToNextLevel;


        m_level++;


        levelsGained++;


        m_xpToNextLevel =
            CalculateRequiredXP(
                m_level
            );
    }


    return levelsGained;
}


int PlayerProgress::GetLevel() const
{
    return m_level;
}


int PlayerProgress::GetCurrentXP() const
{
    return m_currentXP;
}


int PlayerProgress::GetXPToNextLevel() const
{
    return m_xpToNextLevel;
}


int PlayerProgress::CalculateRequiredXP(
    int level
)
{
    return
        BASE_XP_REQUIREMENT +
        (
            level - 1
        ) *
        XP_INCREASE_PER_LEVEL;
}