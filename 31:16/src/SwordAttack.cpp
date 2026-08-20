#include "SwordAttack.hpp"
#include "WeaponDraw.hpp"

#include "Enemy.hpp"

#include <cmath>


namespace
{
    constexpr float SWORD_LENGTH =
        85.0f;


    constexpr float SWORD_WIDTH =
        45.0f;


    constexpr float SWORD_OFFSET =
        20.0f;


    constexpr float SWORD_LIFETIME =
        0.20f;
}


SwordAttack::SwordAttack(
    Vector2 position,
    Vector2 direction,
    int damage
)
    : MeleeAttack(damage),
      m_ownerPosition(position),
      m_direction(direction),
      m_lifetime(SWORD_LIFETIME)
{
}


void SwordAttack::Update(
    float dt,
    Vector2 ownerPosition
)
{
    if (m_expired)
    {
        return;
    }


    // Sword stays attached to player
    // during the short attack.
    m_ownerPosition =
        ownerPosition;


    m_lifetime -= dt;


    if (m_lifetime <= 0.0f)
    {
        Destroy();
    }
}


void SwordAttack::Draw() const
{
    Vector2 start =
    {
        m_ownerPosition.x +
            m_direction.x *
            SWORD_OFFSET,

        m_ownerPosition.y +
            m_direction.y *
            SWORD_OFFSET
    };


    float angle =
        std::atan2(
            m_direction.y,
            m_direction.x
        ) * RAD2DEG;


    WeaponDraw::DrawJalurGemilangSlash(
        start,
        angle,
        1.0f
    );

}


bool SwordAttack::CanDamage() const
{
    return !m_expired;
}


bool SwordAttack::CheckCollision(
    const Enemy& enemy
) const
{
    Vector2 enemyPosition =
        enemy.GetPosition();


    float enemyRadius =
        enemy.GetRadius();


    Vector2 start =
    {
        m_ownerPosition.x +
            m_direction.x *
            SWORD_OFFSET,

        m_ownerPosition.y +
            m_direction.y *
            SWORD_OFFSET
    };


    Vector2 relative =
    {
        enemyPosition.x - start.x,
        enemyPosition.y - start.y
    };


    // Distance along sword direction.
    float along =
        relative.x * m_direction.x +
        relative.y * m_direction.y;


    // Perpendicular distance.
    float perpendicular =
        std::fabs(
            relative.x * -m_direction.y +
            relative.y * m_direction.x
        );


    bool insideLength =
        along + enemyRadius >= 0.0f &&
        along - enemyRadius <= SWORD_LENGTH;


    bool insideWidth =
        perpendicular <=
        SWORD_WIDTH / 2.0f +
        enemyRadius;


    return
        insideLength &&
        insideWidth;
}