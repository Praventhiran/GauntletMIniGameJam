#pragma once


#include "EnemyType.hpp"

class WaveManager
{
public:
    WaveManager();

    void Update(float dt);

    bool CanSpawn(EnemyType type) const;

private:
    float m_gameTime;

};