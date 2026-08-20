#include "BoomerangProjectile.hpp"

#include <cmath>


namespace
{
    constexpr float BOOMERANG_SPEED = 350.0f;

    constexpr float BOOMERANG_MAX_DISTANCE = 250.0f;

    constexpr float BOOMERANG_CATCH_RADIUS = 20.0f;

    constexpr float BOOMERANG_MAX_LIFETIME = 6.0f;
}


BoomerangProjectile::BoomerangProjectile(
    Vector2 position,
    Vector2 direction,
    int damage
)
    : Projectile(position, 8.0f, damage),
      m_direction(direction),
      m_ownerPosition(position),
      m_speed(BOOMERANG_SPEED),
      m_distanceTravelled(0.0f),
      m_maxDistance(BOOMERANG_MAX_DISTANCE),
      m_lifetime(BOOMERANG_MAX_LIFETIME),
      m_returning(false),
      m_canHit(true)
{
}


void BoomerangProjectile::Update(float dt)
{
    if (m_destroyed)
    {
        return;
    }


    // Safety lifetime.
    m_lifetime -= dt;


    if (m_lifetime <= 0.0f)
    {
        Destroy();

        return;
    }


    // -------------------------
    // OUTGOING
    // -------------------------

    if (!m_returning)
    {
        float distanceThisFrame =
            m_speed * dt;


        m_position.x +=
            m_direction.x *
            distanceThisFrame;


        m_position.y +=
            m_direction.y *
            distanceThisFrame;


        m_distanceTravelled +=
            distanceThisFrame;


        if (m_distanceTravelled >= m_maxDistance)
        {
            m_returning = true;


            // Allow another enemy hit
            // on the return journey.
            m_canHit = true;
        }


        return;
    }


    // -------------------------
    // RETURNING
    // -------------------------

    Vector2 toOwner =
    {
        m_ownerPosition.x - m_position.x,

        m_ownerPosition.y - m_position.y
    };


    float distanceSquared =
        toOwner.x * toOwner.x +
        toOwner.y * toOwner.y;


    float catchRadiusSquared =
        BOOMERANG_CATCH_RADIUS *
        BOOMERANG_CATCH_RADIUS;


    // Already close enough to player.
    if (distanceSquared <= catchRadiusSquared)
    {
        Destroy();

        return;
    }


    float distance =
        std::sqrt(distanceSquared);


    float step =
        m_speed * dt;


    // Prevent overshooting the player.
    if (step >= distance)
    {
        m_position = m_ownerPosition;

        Destroy();

        return;
    }


    toOwner.x /= distance;

    toOwner.y /= distance;


    m_position.x +=
        toOwner.x *
        step;


    m_position.y +=
        toOwner.y *
        step;
}


void BoomerangProjectile::Draw() const
{
    DrawCircle(
        static_cast<int>(m_position.x),
        static_cast<int>(m_position.y),
        m_radius,
        ORANGE
    );
}


bool BoomerangProjectile::CanHitEnemy() const
{
    return
        !m_destroyed &&
        m_canHit;
}


void BoomerangProjectile::OnEnemyHit()
{
    // One enemy can be hit during this leg
    // of the boomerang journey.
    m_canHit = false;
}


void BoomerangProjectile::SetOwnerPosition(
    Vector2 ownerPosition
)
{
    m_ownerPosition =
        ownerPosition;
}