#include "MeleeAttack.hpp"

#include "Enemy.hpp"


MeleeAttack::MeleeAttack(int damage)
    : m_damage(damage),
      m_expired(false)
{
}


bool MeleeAttack::TryHitEnemy(
    Enemy& enemy
)
{
    if (m_expired)
    {
        return false;
    }


    if (!CanDamage())
    {
        return false;
    }


    if (enemy.IsDead())
    {
        return false;
    }


    if (
        m_hitEnemies.count(&enemy) > 0
    )
    {
        return false;
    }


    if (!CheckCollision(enemy))
    {
        return false;
    }


    enemy.TakeDamage(
        m_damage
    );


    m_hitEnemies.insert(
        &enemy
    );


    return true;
}


void MeleeAttack::ApplySecondaryEffect(
    Enemy& enemy
)
{
    (void)enemy;
}


void MeleeAttack::FinishFrame()
{
    // Default melee attacks need
    // no end-of-frame behaviour.
}


bool MeleeAttack::IsExpired() const
{
    return m_expired;
}


void MeleeAttack::Destroy()
{
    m_expired = true;
}