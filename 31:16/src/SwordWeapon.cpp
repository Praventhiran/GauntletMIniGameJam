#include "SwordWeapon.hpp"

#include "GameContext.hpp"
#include "MeleeManager.hpp"


SwordWeapon::SwordWeapon()
    : MeleeWeapon(
        {
            35,
            0.7f,
            1
        }
    )
{
}


void SwordWeapon::SpawnMeleeAttack(
    Vector2 position,
    Vector2 direction,
    GameContext& context
)
{
    context.meleeManager.SpawnSword(
        position,
        direction,
        m_stats.damage
    );
}



WeaponType SwordWeapon::GetType() const
{
    return WeaponType::Sword;
}


const char* SwordWeapon::GetDisplayName() const
{
    return "JALUR GEMILANG";
}


const char* SwordWeapon::GetUpgradeName() const
{
    switch (m_level)
    {
        case 1:
            return "SEMANGAT MERDEKA";

        case 2:
            return "KIBARAN PANTAS";

        case 3:
            return "DUA KIBARAN";

        case 4:
            return "JALUR GEMILANG!";

        default:
            return "MAX LEVEL";
    }
}


const char* SwordWeapon::GetUpgradeDescription() const
{
    switch (m_level)
    {
        case 1:
            return "Flag strikes deal +15 damage.";

        case 2:
            return "Swing the flag 20% faster.";

        case 3:
            return "Perform 1 additional flag slash.";

        case 4:
            return "+25 damage and 15% faster swings.";

        default:
            return "Maximum patriotic power!";
    }
}


void SwordWeapon::ApplyUpgrade(int newLevel)
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