#include "WaveManager.hpp"


WaveManager::WaveManager()
    : m_gameTime(0.0f)
{
}

void WaveManager::Update(float dt)
{
    m_gameTime += dt;
}

bool WaveManager::CanSpawn(EnemyType type) const
{
    switch (type)
    {
        case EnemyType::Basic:
            return m_gameTime >= 0.0f; // Basic enemies can spawn immediately
        case EnemyType::Fast:
            return m_gameTime >= 30.0f; // Fast enemies can spawn after 30 seconds
        case EnemyType::Tank:
            return m_gameTime >= 60.0f; // Tank enemies can spawn after 60 seconds
        default:
            return false;
    }
}