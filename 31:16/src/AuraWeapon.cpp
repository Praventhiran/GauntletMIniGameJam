#include "AuraWeapon.hpp"

#include "GameContext.hpp"
#include "MeleeManager.hpp"


AuraWeapon::AuraWeapon()
    : MeleeWeapon(
        {
            5,     // damage
            6.0f,   // cooldown
            1       // amount
        }
    )
{
}


bool AuraWeapon::RequiresAim() const
{
    return false;
}


void AuraWeapon::SpawnMeleeAttack(
    Vector2 position,
    Vector2 direction,
    GameContext& context
)
{
    // Aura doesn't use direction.
    (void)direction;


    context.meleeManager.SpawnAura(
        position,
        m_stats.damage
    );
}


WeaponType AuraWeapon::GetType() const
{
    return WeaponType::Aura;
}


const char* AuraWeapon::GetDisplayName() const
{
    return "DURIAN SMELL";
}


const char* AuraWeapon::GetUpgradeName() const
{
    switch (m_level)
    {
        case 1:
            return "EXTRA RIPE";

        case 2:
            return "BAU LAGI KUAT";

        case 3:
            return "MUSANG KING";

        case 4:
            return "DILARANG BAWA MASUK";

        default:
            return "MAX LEVEL";
    }
}


const char* AuraWeapon::GetUpgradeDescription() const
{
    switch (m_level)
    {
        case 1:
            return "Extra-ripe fumes deal +10 damage.";

        case 2:
            return "Durian smell attacks 15% faster.";

        case 3:
            return "Musang King fumes deal +15 damage.";

        case 4:
            return "+25 damage and 20% faster attacks.";

        default:
            return "The smell cannot get any worse.";
    }
}


void AuraWeapon::ApplyUpgrade(int newLevel)
{
    switch (newLevel)
    {
        case 2:
            m_stats.damage += 10;
            break;

        case 3:
            m_stats.cooldown *= 0.85f;
            break;

        case 4:
            m_stats.damage += 15;
            break;

        case 5:
            m_stats.damage += 25;
            m_stats.cooldown *= 0.80f;
            break;

        default:
            break;
    }
}