#include "MeleeManager.hpp"

#include "SwordAttack.hpp"
#include "BeamAttack.hpp"
#include "AuraAttack.hpp"

#include <algorithm>


void MeleeManager::SpawnSword(
    Vector2 position,
    Vector2 direction,
    int damage
)
{
    m_attacks.push_back(
        std::make_unique<SwordAttack>(
            position,
            direction,
            damage
        )
    );
}


void MeleeManager::SpawnBeam(
    Vector2 position,
    Vector2 direction,
    int damage
)
{
    m_attacks.push_back(
        std::make_unique<BeamAttack>(
            position,
            direction,
            damage
        )
    );
}


void MeleeManager::SpawnAura(
    Vector2 position,
    int damage
)
{
    m_attacks.push_back(
        std::make_unique<AuraAttack>(
            position,
            damage
        )
    );
}


void MeleeManager::Update(
    float dt,
    std::vector<std::unique_ptr<Enemy>>& enemies,
    Vector2 playerPosition
)
{
    // Update attacks.
    for (auto& attack : m_attacks)
    {
        attack->Update(
            dt,
            playerPosition
        );
    }


    // Attack vs enemy.
    for (auto& attack : m_attacks)
    {
        if (attack->IsExpired())
        {
            continue;
        }


        for (auto& enemy : enemies)
        {
            if (enemy->IsDead())
            {
                continue;
            }


            // Normal damage.
            attack->TryHitEnemy(
                *enemy
            );

            // Knockback 
            attack->ApplySecondaryEffect(
                *enemy
            );


            attack->FinishFrame();

        }

        

 
    }


    // Remove finished attacks.
    m_attacks.erase(

        std::remove_if(
            m_attacks.begin(),
            m_attacks.end(),

            [](
                const std::unique_ptr<MeleeAttack>& attack
            )
            {
                return attack->IsExpired();
            }
        ),

        m_attacks.end()
    );
}


void MeleeManager::Draw() const
{
    for (const auto& attack : m_attacks)
    {
        attack->Draw();
    }
}