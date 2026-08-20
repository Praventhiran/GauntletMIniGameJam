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