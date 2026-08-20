#include "BeamAttack.hpp"
#include "WeaponDraw.hpp"



#include "Enemy.hpp"
#include "raylib.h"

#include <cmath>


namespace
{
    constexpr float BEAM_WIDTH =
        70.0f;


    constexpr float CHARGE_STAGE_ONE =
        0.6f;


    constexpr float CHARGE_STAGE_TWO =
        0.6f;


    constexpr float ACTIVE_DURATION =
        1.5f;


    constexpr float TOTAL_CHARGE_TIME =
        CHARGE_STAGE_ONE +
        CHARGE_STAGE_TWO;


    constexpr float TOTAL_LIFETIME =
        TOTAL_CHARGE_TIME +
        ACTIVE_DURATION;
}


BeamAttack::BeamAttack(
    Vector2 position,
    Vector2 direction,
    int damage
)
    : MeleeAttack(damage),
      m_ownerPosition(position),
      m_direction(direction),
      m_elapsedTime(0.0f),
      m_opacity(0.0f),
      m_damageActive(false)
{
}


void BeamAttack::Update(
    float dt,
    Vector2 ownerPosition
)
{
    if (m_expired)
    {
        return;
    }


    // Beam follows player's current position.
    m_ownerPosition =
        ownerPosition;


    m_elapsedTime += dt;


    // -------------------------
    // CHARGE: 0% -> 50%
    // -------------------------

    if (m_elapsedTime <
        CHARGE_STAGE_ONE)
    {
        float progress =
            m_elapsedTime /
            CHARGE_STAGE_ONE;


        m_opacity =
            progress * 0.5f;


        m_damageActive =
            false;


        return;
    }


    // -------------------------
    // CHARGE: 50% -> 100%
    // -------------------------

    if (m_elapsedTime <
        TOTAL_CHARGE_TIME)
    {
        float stageTime =
            m_elapsedTime -
            CHARGE_STAGE_ONE;


        float progress =
            stageTime /
            CHARGE_STAGE_TWO;


        m_opacity =
            0.5f +
            progress * 0.5f;


        m_damageActive =
            false;


        return;
    }


    // -------------------------
    // FULL POWER
    // -------------------------

    if (m_elapsedTime <
        TOTAL_LIFETIME)
    {
        m_opacity =
            1.0f;


        m_damageActive =
            true;


        return;
    }


    Destroy();
}


float BeamAttack::GetBeamLength() const
{
    float width =
        static_cast<float>(
            GetScreenWidth()
        );


    float height =
        static_cast<float>(
            GetScreenHeight()
        );


    // Screen diagonal guarantees the beam
    // reaches beyond the screen edge.
    return std::sqrt(
        width * width +
        height * height
    );
}


void BeamAttack::Draw() const
{
    Vector2 start =
    {
        m_ownerPosition.x,
        m_ownerPosition.y
    };


    Vector2 end =
    {
        m_ownerPosition.x +
            m_direction.x * 1000.0f,

        m_ownerPosition.y +
            m_direction.y * 1000.0f
    };


    WeaponDraw::DrawTehTarikBeam(
        start,
        end,
        m_opacity
    );
}


bool BeamAttack::CanDamage() const
{
    return
        !m_expired &&
        m_damageActive;
}


bool BeamAttack::CheckCollision(
    const Enemy& enemy
) const
{
    if (!m_damageActive)
    {
        return false;
    }


    Vector2 enemyPosition =
        enemy.GetPosition();


    float enemyRadius =
        enemy.GetRadius();


    Vector2 relative =
    {
        enemyPosition.x -
            m_ownerPosition.x,

        enemyPosition.y -
            m_ownerPosition.y
    };


    float along =
        relative.x * m_direction.x +
        relative.y * m_direction.y;


    float perpendicular =
        std::fabs(
            relative.x * -m_direction.y +
            relative.y * m_direction.x
        );


    float beamLength =
        GetBeamLength();


    bool insideLength =
        along + enemyRadius >= 0.0f &&
        along - enemyRadius <=
            beamLength;


    bool insideWidth =
        perpendicular <=
        BEAM_WIDTH / 2.0f +
        enemyRadius;


    return
        insideLength &&
        insideWidth;
}
