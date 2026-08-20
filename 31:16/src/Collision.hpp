#pragma once

#include "Entity.hpp"


class Collision
{
public:

    static bool Check(
        const Entity& a,
        const Entity& b
    );


    // if their circles overlap.
    static bool ResolveOverlap(Entity& movable, const Entity& fixed);
        
};