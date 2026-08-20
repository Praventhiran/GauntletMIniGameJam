#include "BeamWeapon.hpp"

#include "GameContext.hpp"
#include "MeleeManager.hpp"


BeamWeapon::BeamWeapon()
    : MeleeWeapon(
        {
            80,
            4.0f,
            1
        }
    )
{
}


void BeamWeapon::SpawnMeleeAttack(
    Vector2 position,
    Vector2 direction,
    GameContext& context
)
{
    context.meleeManager.SpawnBeam(
        position,
        direction,
        m_stats.damage
    );
}



WeaponType BeamWeapon::GetType() const
{
    return WeaponType::Beam;
}


const char* BeamWeapon::GetDisplayName() const
{
    return "TEH TARIK BEAM";
}


const char* BeamWeapon::GetUpgradeName() const
{
    switch (m_level)
    {
        case 1:
            return "TEH KAW";

        case 2:
            return "TARIK LAGI!";

        case 3:
            return "DOUBLE POUR";

        case 4:
            return "MAMAK POWER";

        default:
            return "MAX LEVEL";
    }
}


const char* BeamWeapon::GetUpgradeDescription() const
{
    switch (m_level)
    {
        case 1:
            return "Stronger teh tarik deals +30 damage.";

        case 2:
            return "Prepare teh tarik 15% faster.";

        case 3:
            return "Fire 1 additional teh tarik beam.";

        case 4:
            return "+40 damage and 20% faster firing.";

        default:
            return "Maximum teh tarik power!";
    }
}


void BeamWeapon::ApplyUpgrade(int newLevel)
{
    switch (newLevel)
    {
        case 2:
            m_stats.damage += 30;
            break;

        case 3:
            m_stats.cooldown *= 0.85f;
            break;

        case 4:
            m_stats.amount += 1;
            break;

        case 5:
            m_stats.damage += 40;
            m_stats.cooldown *= 0.80f;
            break;

        default:
            break;
    }
}