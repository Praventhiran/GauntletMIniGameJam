#pragma once

#include "raylib.h"


class Entity
{
public:
    Entity(Vector2 position, float radius);

    virtual ~Entity() = default;

    // Every entity can update differently.
    virtual void Update(float dt);

    //Every entity can draw differently.
    virtual void Draw() const;

    // Getters
    Vector2 GetPosition() const;
    float GetRadius() const;

    void Translate(Vector2 delta);

protected:
    Vector2 m_position;

    float m_radius;
}; 
    