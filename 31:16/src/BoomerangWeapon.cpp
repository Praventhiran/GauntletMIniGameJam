#include "BoomerangWeapon.hpp"

#include "GameContext.hpp"
#include "ProjectileManager.hpp"


BoomerangWeapon::BoomerangWeapon()
    : ProjectileWeapon(
        {
            40,     // damage - suggested
            1.2f,   // cooldown - suggested
            1       // amount
        }
    )
{
}


void BoomerangWeapon::SpawnProjectile(
    Vector2 position,
    Vector2 direction,
    GameContext& context
)
{
    context.projectileManager.SpawnBoomerang(
        position,
        direction,
        m_stats.damage
    );
}