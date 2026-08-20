#include "Enemy.hpp"

#include <cmath>


namespace
{
    // Higher number = knockback stops faster.
    constexpr float KNOCKBACK_DAMPING =
        6.0f;


    constexpr float MAX_KNOCKBACK_SPEED =
        900.0f;


    constexpr float MIN_KNOCKBACK_SPEED =
        5.0f;


    constexpr float MIN_DIRECTION_LENGTH_SQUARED =
        0.0001f;
}


Enemy::Enemy(
    Vector2 position,
    EnemyType type
)
    : Actor(position, 50),
      m_speed(200.0f),
      m_color(RED),
      m_target(position),
      m_knockbackVelocity({ 0.0f, 0.0f })
{
    switch (type)
    {
        case EnemyType::Basic:

            m_health = 100;
            m_speed = 80.0f;
            m_color = RED;

            break;


        case EnemyType::Fast:

            m_health = 30;
            m_speed = 150.0f;
            m_color = BLUE;

            break;


        case EnemyType::Tank:

            m_health = 200;
            m_speed = 40.0f;
            m_color = PURPLE;

            break;
    }
}


void Enemy::Update(float dt)
{
    if (IsDead())
    {
        return;
    }


    // --------------------------------
    // NORMAL MOVEMENT TOWARD PLAYER
    // --------------------------------

    Vector2 direction =
    {
        m_target.x - m_position.x,
        m_target.y - m_position.y
    };


    float distanceSquared =
        direction.x * direction.x +
        direction.y * direction.y;


    if (
        distanceSquared >
        MIN_DIRECTION_LENGTH_SQUARED
    )
    {
        float distance =
            std::sqrt(distanceSquared);


        direction.x /= distance;
        direction.y /= distance;


        m_position.x +=
            direction.x *
            m_speed *
            dt;


        m_position.y +=
            direction.y *
            m_speed *
            dt;
    }


    // --------------------------------
    // KNOCKBACK MOVEMENT
    // --------------------------------

    m_position.x +=
        m_knockbackVelocity.x *
        dt;


    m_position.y +=
        m_knockbackVelocity.y *
        dt;


    // Frame-rate independent-ish exponential damping.
    float damping =
        std::exp(
            -KNOCKBACK_DAMPING *
            dt
        );


    m_knockbackVelocity.x *=
        damping;


    m_knockbackVelocity.y *=
        damping;


    float knockbackSpeedSquared =
        m_knockbackVelocity.x *
        m_knockbackVelocity.x +

        m_knockbackVelocity.y *
        m_knockbackVelocity.y;


    if (
        knockbackSpeedSquared <
        MIN_KNOCKBACK_SPEED *
        MIN_KNOCKBACK_SPEED
    )
    {
        m_knockbackVelocity =
        {
            0.0f,
            0.0f
        };
    }
}


void Enemy::ApplyKnockback(
    Vector2 direction,
    float force
)
{
    float lengthSquared =
        direction.x * direction.x +
        direction.y * direction.y;


    if (
        lengthSquared <=
        MIN_DIRECTION_LENGTH_SQUARED
    )
    {
        // Rare case: enemy is exactly
        // at the knockback origin.
        direction =
        {
            1.0f,
            0.0f
        };
    }
    else
    {
        float length =
            std::sqrt(lengthSquared);


        direction.x /= length;

        direction.y /= length;
    }


    // Add impulse.
    m_knockbackVelocity.x +=
        direction.x *
        force;


    m_knockbackVelocity.y +=
        direction.y *
        force;


    // Prevent multiple effects from creating
    // ridiculous knockback speeds.
    float speedSquared =
        m_knockbackVelocity.x *
        m_knockbackVelocity.x +

        m_knockbackVelocity.y *
        m_knockbackVelocity.y;


    if (
        speedSquared >
        MAX_KNOCKBACK_SPEED *
        MAX_KNOCKBACK_SPEED
    )
    {
        float speed =
            std::sqrt(speedSquared);


        m_knockbackVelocity.x =
            (
                m_knockbackVelocity.x /
                speed
            ) *
            MAX_KNOCKBACK_SPEED;


        m_knockbackVelocity.y =
            (
                m_knockbackVelocity.y /
                speed
            ) *
            MAX_KNOCKBACK_SPEED;
    }
}


void Enemy::SetTarget(Vector2 target)
{
    m_target = target;
}


void Enemy::Draw() const
{
    DrawCircle(
        static_cast<int>(m_position.x),
        static_cast<int>(m_position.y),
        m_radius,
        m_color
    );
}