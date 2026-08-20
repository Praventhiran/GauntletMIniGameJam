#pragma once

#include "Actor.hpp"
#include "EnemyType.hpp"


class Enemy : public Actor
{
public:
    Enemy(Vector2 position,EnemyType type);

    //enemy overides the parent
    void Update(float dt) override;
    //enemy adds a new function to set the target position
    void SetTarget(Vector2 target);

    void Draw() const override;

    void ApplyKnockback(Vector2 direction, float force);
        
        
   

private:
    float m_speed;
    Color m_color;
    Vector2 m_target;
    Vector2 m_knockbackVelocity;
};