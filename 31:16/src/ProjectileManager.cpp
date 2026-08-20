#include "ProjectileManager.hpp"

#include "BulletProjectile.hpp"
#include "BoomerangProjectile.hpp"
#include "Collision.hpp"

#include <algorithm>


void ProjectileManager::SpawnBullet(
    Vector2 position,
    Vector2 direction,
    int damage,
    float speed
)
{
    m_projectiles.push_back(
        std::make_unique<BulletProjectile>(
            position,
            direction,
            damage,
            speed
        )
    );
}


void ProjectileManager::SpawnBoomerang(
    Vector2 position,
    Vector2 direction,
    int damage
)
{
    m_projectiles.push_back(
        std::make_unique<BoomerangProjectile>(
            position,
            direction,
            damage
        )
    );
}


void ProjectileManager::Update(
    float dt,
    std::vector<std::unique_ptr<Enemy>>& enemies,
    Vector2 playerPosition
)
{
    // -------------------------
    // UPDATE PROJECTILES
    // -------------------------

    for (auto& projectile : m_projectiles)
    {
        // Relevant to boomerangs.
        // Normal bullets simply ignore this.
        projectile->SetOwnerPosition(
            playerPosition
        );


        projectile->Update(dt);
    }


    // -------------------------
    // PROJECTILE VS ENEMY
    // -------------------------

    for (auto& projectile : m_projectiles)
    {
        if (projectile->IsExpired())
        {
            continue;
        }


        if (!projectile->CanHitEnemy())
        {
            continue;
        }


        for (auto& enemy : enemies)
        {
            if (enemy->IsDead())
            {
                continue;
            }


            if (
                Collision::Check(
                    *projectile,
                    *enemy
                )
            )
            {
                enemy->TakeDamage(
                    projectile->GetDamage()
                );


                // Projectile decides what happens.
                projectile->OnEnemyHit();


                // Bullet will now be destroyed.
                // Boomerang may simply temporarily
                // disable further hits.
                if (
                    projectile->IsExpired() ||
                    !projectile->CanHitEnemy()
                )
                {
                    break;
                }
            }
        }
    }


    // -------------------------
    // REMOVE DEAD PROJECTILES
    // -------------------------

    m_projectiles.erase(

        std::remove_if(
            m_projectiles.begin(),
            m_projectiles.end(),

            [](
                const std::unique_ptr<Projectile>& projectile
            )
            {
                return projectile->IsExpired();
            }
        ),

        m_projectiles.end()
    );
}


void ProjectileManager::Draw() const
{
    for (const auto& projectile : m_projectiles)
    {
        projectile->Draw();
    }
}