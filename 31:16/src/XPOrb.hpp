#pragma once

#include "Entity.hpp"


class XPOrb : public Entity
{
public:

    XPOrb(
        Vector2 position,
        int value
    );


    void Update(float dt) override;


    void Draw() const override;


    int GetValue() const;


private:

    int m_value;

    float m_elapsedTime;
};