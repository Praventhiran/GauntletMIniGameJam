#include "BulletProjectile.hpp"
#include "WeaponDraw.hpp"


namespace
{
    constexpr float BULLET_LIFETIME = 2.0f;
}


BulletProjectile::BulletProjectile(
    Vector2 position,
    Vector2 direction,
    int damage,
    float speed
)
    : Projectile(position, 5.0f, damage),
      m_direction(direction),
      m_speed(speed),
      m_lifetime(BULLET_LIFETIME)
{
}


void BulletProjectile::Update(float dt)
{
    if (m_destroyed)
    {
        return;
    }


    m_position.x +=
        m_direction.x *
        m_speed *
        dt;


    m_position.y +=
        m_direction.y *
        m_speed *
        dt;


    m_lifetime -= dt;


    if (m_lifetime <= 0.0f)
    {
        Destroy();
    }
}


void BulletProjectile::Draw() const
{
    WeaponDraw::DrawFireworkLauncher(
        m_position,
        m_direction,
        1.0f
    );
}


void BulletProjectile::OnEnemyHit()
{
    // Normal bullet disappears after hitting one enemy.
    Destroy();
}