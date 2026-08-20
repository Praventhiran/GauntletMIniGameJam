#include "BasicGunWeapon.hpp"

#include "GameContext.hpp"
#include "ProjectileManager.hpp"


namespace
{
    constexpr float BULLET_SPEED =
        400.0f;
}


BasicGunWeapon::BasicGunWeapon()
    : ProjectileWeapon(
        {
            25,     // damage
            0.5f,   // cooldown
            1       // amount
        }
    )
{
}


void BasicGunWeapon::SpawnProjectile(
    Vector2 position,
    Vector2 direction,
    GameContext& context
)
{
    context.projectileManager.SpawnBullet(
        position,
        direction,
        m_stats.damage,
        BULLET_SPEED
    );
}