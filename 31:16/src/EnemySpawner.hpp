#pragma once

#include "Enemy.hpp"
#include "WaveManager.hpp"

#include <memory>
#include <vector>


class EnemySpawner
{
public:

    EnemySpawner();


    void Update(
        float dt,
        const Vector2& playerPosition
    );


    void RemoveDeadEnemies();


    std::vector<std::unique_ptr<Enemy>>& GetEnemies();


private:

    float m_spawnTimer;

    std::vector<std::unique_ptr<Enemy>> m_enemies;

    WaveManager m_waveManager;
};