#include "Entity.hpp"


Entity::Entity(Vector2 position, float radius)
    : m_position(position),
      m_radius(radius)
{
}

void Entity::Update(float dt)
{
    (void)dt; // Unused parameter
}

void Entity::Draw() const
{
    //does nothing
}

Vector2 Entity::GetPosition() const
{
    return m_position;
}

float Entity::GetRadius() const
{
    return m_radius;
}

void Entity::Translate(Vector2 delta)
{
    m_position.x += delta.x;
    m_position.y += delta.y;
}