#pragma once

#include "raylib.h"
#include "XPOrb.hpp"

#include <memory>
#include <vector>


class Entity;


class XPManager
{
public:

    void Spawn(
        Vector2 position,
        int value
    );


    int Update(
        float dt,
        const Entity& player
    );


    void Draw() const;


private:

    std::vector<
        std::unique_ptr<XPOrb>
    > m_orbs;
};