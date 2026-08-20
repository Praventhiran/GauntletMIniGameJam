#pragma once


class PlayerProgress
{
public:

    PlayerProgress();


    int AddXP(int amount);


    int GetLevel() const;

    int GetCurrentXP() const;

    int GetXPToNextLevel() const;


private:

    static int CalculateRequiredXP(
        int level
    );


    int m_level;

    int m_currentXP;

    int m_xpToNextLevel;
};