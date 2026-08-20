#pragma once

#include "Entity.hpp"


class Actor : public Entity
{
public:

    // Constructor to initialize the Actor with a position and health
    Actor(Vector2 position, int health);

    void TakeDamage(int amount);

    bool IsDead() const;

    int GetHealth() const;

    int GetMaxHealth() const;

protected:
    int m_health;
    int m_maxHealth;
};
