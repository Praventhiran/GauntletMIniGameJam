#pragma once

#include "raylib.h"


class HealthBar
{
public:

    explicit HealthBar(int maxHealth);


    void Update(float dt);


    void OnDamage();


    void Draw(int currentHealth) const;


private:

    int m_maxHealth;


    float m_punchTimer;

    float m_shakeTimer;

    float m_flashTimer;
};