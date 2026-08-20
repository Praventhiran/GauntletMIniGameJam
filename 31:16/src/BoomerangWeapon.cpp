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



WeaponType BoomerangWeapon::GetType() const
{
    return WeaponType::Boomerang;
}


const char* BoomerangWeapon::GetDisplayName() const
{
    return "ROTI CANAI";
}


const char* BoomerangWeapon::GetUpgradeName() const
{
    switch (m_level)
    {
        case 1:
            return "ROTI BANJIR";

        case 2:
            return "ROTI TERBANG";

        case 3:
            return "ROTI KOSONG DUA!";

        case 4:
            return "MAMAK SPECIAL";

        default:
            return "MAX LEVEL";
    }
}


const char* BoomerangWeapon::GetUpgradeDescription() const
{
    switch (m_level)
    {
        case 1:
            return "Gravy-powered roti deals +15 damage.";

        case 2:
            return "Throw roti 20% faster.";

        case 3:
            return "Throw 1 additional roti.";

        case 4:
            return "+25 damage and 15% faster throws.";

        default:
            return "Maximum mamak power!";
    }
}


void BoomerangWeapon::ApplyUpgrade(int newLevel)
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