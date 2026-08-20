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