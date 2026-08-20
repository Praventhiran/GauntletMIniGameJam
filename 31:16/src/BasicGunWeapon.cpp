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



WeaponType BasicGunWeapon::GetType() const
{
    return WeaponType::BasicGun;
}


const char* BasicGunWeapon::GetDisplayName() const
{
    return "FIREWORK LAUNCHER";
}


const char* BasicGunWeapon::GetUpgradeName() const
{
    switch (m_level)
    {
        case 1:
            return "BIGGER BOOM";

        case 2:
            return "RAPID CELEBRATION";

        case 3:
            return "DOUBLE FIREWORKS";

        case 4:
            return "MERDEKA FINALE";

        default:
            return "MAX LEVEL";
    }
}


const char* BasicGunWeapon::GetUpgradeDescription() const
{
    switch (m_level)
    {
        case 1:
            return "Fireworks deal +15 damage.";

        case 2:
            return "Launch fireworks 20% faster.";

        case 3:
            return "Launch 1 additional firework.";

        case 4:
            return "+25 damage and 15% faster firing.";

        default:
            return "Maximum firework power!";
    }
}


void BasicGunWeapon::ApplyUpgrade(int newLevel)
{
    switch (newLevel)
    {
        case 2:
            m_stats.damage += 15;
            break;

        case 3:
            m_stats.cooldown *= 0.80f;
            break;

        case 4:
            m_stats.amount += 1;
            break;

        case 5:
            m_stats.damage += 25;
            m_stats.cooldown *= 0.85f;
            break;

        default:
            break;
    }
}