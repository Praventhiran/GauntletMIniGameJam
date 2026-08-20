#pragma once


class ExperienceBar
{
public:

    ExperienceBar();


    void Update(float dt);


    void OnXPCollected();


    void OnLevelUp();


    void Draw(
        int level,
        int currentXP,
        int requiredXP
    ) const;


private:

    float m_xpPunchTimer;

    float m_levelUpTimer;
};