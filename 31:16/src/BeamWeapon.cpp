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