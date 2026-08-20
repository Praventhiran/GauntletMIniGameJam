#include "EnemySpawner.hpp"
#include "EnemySeparation.hpp"
#include "raylib.h"

#include <algorithm>
#include <cmath>
#include <vector>


namespace
{
    constexpr float SPAWN_INTERVAL = 2.0f;
    constexpr float SPAWN_DISTANCE = 500.0f;


    Vector2 GetRandomSpawnPosition(
        const Vector2& playerPosition
    )
    {
        float angle =
            static_cast<float>(
                GetRandomValue(0, 359)
            ) * DEG2RAD;


        return
        {
            playerPosition.x +
                std::cos(angle) * SPAWN_DISTANCE,

            playerPosition.y +
                std::sin(angle) * SPAWN_DISTANCE
        };
    }
}


EnemySpawner::EnemySpawner()
    : m_spawnTimer(0.0f)
{
}


void EnemySpawner::Update(
    float dt,
    const Vector2& playerPosition
)
{
    m_waveManager.Update(dt);

    m_spawnTimer += dt;


    if (m_spawnTimer >= SPAWN_INTERVAL)
    {
        // Keep leftover frame time.
        m_spawnTimer -= SPAWN_INTERVAL;


        std::vector<EnemyType> spawnableTypes;


        if (m_waveManager.CanSpawn(EnemyType::Basic))
        {
            spawnableTypes.push_back(
                EnemyType::Basic
            );
        }


        if (m_waveManager.CanSpawn(EnemyType::Fast))
        {
            spawnableTypes.push_back(
                EnemyType::Fast
            );
        }


        if (m_waveManager.CanSpawn(EnemyType::Tank))
        {
            spawnableTypes.push_back(
                EnemyType::Tank
            );
        }


        if (!spawnableTypes.empty())
        {
            int randomIndex =
                GetRandomValue(
                    0,
                    static_cast<int>(
                        spawnableTypes.size()
                    ) - 1
                );


            EnemyType type =
                spawnableTypes[randomIndex];


            Vector2 spawnPosition =
                GetRandomSpawnPosition(
                    playerPosition
                );


            m_enemies.push_back(
                std::make_unique<Enemy>(
                    spawnPosition,
                    type
                )
            );
        }
    }


    // Update enemies.
    for (auto& enemy : m_enemies)
    {
        enemy->SetTarget(playerPosition);

        enemy->Update(dt);
    }


    // Prevent enemies from stacking.
    EnemySeparation::Resolve(m_enemies);
}


void EnemySpawner::RemoveDeadEnemies()
{
    m_enemies.erase(
        std::remove_if(
            m_enemies.begin(),
            m_enemies.end(),

            [](const std::unique_ptr<Enemy>& enemy)
            {
                return enemy->IsDead();
            }
        ),

        m_enemies.end()
    );
}


std::vector<std::unique_ptr<Enemy>>&
EnemySpawner::GetEnemies()
{
    return m_enemies;
}