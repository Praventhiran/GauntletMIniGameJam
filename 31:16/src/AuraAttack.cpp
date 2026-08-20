#include "AuraAttack.hpp"
#include "WeaponDraw.hpp"

#include "Enemy.hpp"

#include <cmath>


namespace
{
    constexpr float AURA_RADIUS =
        140.0f;


    constexpr float AURA_DURATION =
        5.0f;


    constexpr float AURA_DAMAGE_INTERVAL =
        1.0f;


    constexpr float AURA_OPACITY =
        0.18f;


    constexpr float KNOCKBACK_PULSE_OPACITY =
        0.45f;


    // This is velocity, not instant movement.
    constexpr float KNOCKBACK_FORCE =
        700.0f;
}


AuraAttack::AuraAttack(
    Vector2 position,
    int damage
)
    : MeleeAttack(damage),
      m_ownerPosition(position),
      m_elapsedTime(0.0f),
      m_damageTimer(0.0f),
      m_damageTickThisFrame(false),
      m_knockbackTriggered(false),
      m_knockbackThisFrame(false)
{
}


void AuraAttack::Update(
    float dt,
    Vector2 ownerPosition
)
{
    if (m_expired)
    {
        return;
    }


    // Aura follows the player.
    m_ownerPosition =
        ownerPosition;


    float previousElapsedTime =
        m_elapsedTime;


    m_elapsedTime += dt;


    // --------------------------------
    // DAMAGE TIMER
    // --------------------------------

    if (previousElapsedTime < AURA_DURATION)
    {
        m_damageTimer += dt;
    }


    if (
        m_damageTimer >=
        AURA_DAMAGE_INTERVAL
    )
    {
        m_damageTimer -=
            AURA_DAMAGE_INTERVAL;


        m_damageTickThisFrame =
            true;


 
        m_hitEnemies.clear();
    }


    // --------------------------------
    // 5 SECOND KNOCKBACK
    // --------------------------------

    if (
        m_elapsedTime >= AURA_DURATION &&
        !m_knockbackTriggered
    )
    {
        m_knockbackTriggered =
            true;


        m_knockbackThisFrame =
            true;
    }
}


void AuraAttack::Draw() const
{
    float opacity =
        AURA_OPACITY;


    // Flash brighter during knockback.
    if (m_knockbackThisFrame)
    {
        opacity =
            KNOCKBACK_PULSE_OPACITY;
    }


    WeaponDraw::DrawDurianAura(
        m_ownerPosition,
        AURA_RADIUS,
        opacity
    );
}


bool AuraAttack::CanDamage() const
{
    // Damage is ONLY active on the one-second tick frame.

    return
        !m_expired &&
        m_damageTickThisFrame;
}


bool AuraAttack::CheckCollision(
    const Enemy& enemy
) const
{
    Vector2 enemyPosition =
        enemy.GetPosition();


    float dx =
        enemyPosition.x -
        m_ownerPosition.x;


    float dy =
        enemyPosition.y -
        m_ownerPosition.y;


    float distanceSquared =
        dx * dx +
        dy * dy;


    float collisionRadius =
        AURA_RADIUS +
        enemy.GetRadius();


    return
        distanceSquared <=
        collisionRadius *
        collisionRadius;
}


void AuraAttack::ApplySecondaryEffect(
    Enemy& enemy
)
{
    // Knockback happens only once at the end of the 5-second aura.

    if (!m_knockbackThisFrame)
    {
        return;
    }


    if (enemy.IsDead())
    {
        return;
    }


    if (!CheckCollision(enemy))
    {
        return;
    }


    Vector2 enemyPosition =
        enemy.GetPosition();


    Vector2 knockbackDirection =
    {
        enemyPosition.x -
            m_ownerPosition.x,

        enemyPosition.y -
            m_ownerPosition.y
    };


    enemy.ApplyKnockback(
        knockbackDirection,
        KNOCKBACK_FORCE
    );
}


void AuraAttack::FinishFrame()
{
    // The damage window only lasts for this single frame.
  
    m_damageTickThisFrame =
        false;


    if (m_knockbackThisFrame)
    {
        m_knockbackThisFrame =
            false;


        Destroy();
    }
}