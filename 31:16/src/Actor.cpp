#include "Actor.hpp"


Actor::Actor(Vector2 position, int health)
    : Entity(position, 20.0f), m_health(health), m_maxHealth(health)
{
}


void Actor::TakeDamage(int amount)
{
    if (amount <= 0)
    {
        return;
    }


    m_health -= amount;


    if (m_health < 0)
    {
        m_health = 0;
    }
}

bool Actor::IsDead() const
{
    return m_health <= 0;
}

int Actor::GetHealth() const
{
    return m_health;
}

int Actor::GetMaxHealth() const
{
    return m_maxHealth;
}