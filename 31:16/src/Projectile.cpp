#include "Projectile.hpp"


Projectile::Projectile(
    Vector2 position,
    float radius,
    int damage
)
    : Entity(position, radius),
      m_damage(damage),
      m_destroyed(false)
{
}


int Projectile::GetDamage() const
{
    return m_damage;
}


void Projectile::Destroy()
{
    m_destroyed = true;
}


bool Projectile::IsExpired() const
{
    return m_destroyed;
}


bool Projectile::CanHitEnemy() const
{
    return !m_destroyed;
}


void Projectile::SetOwnerPosition(Vector2 ownerPosition)
{
    // Most projectiles don't need the player position.
    (void)ownerPosition;
}