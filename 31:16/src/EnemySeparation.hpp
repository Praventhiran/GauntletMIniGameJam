#pragma once

#include "Enemy.hpp"

#include <vector>
#include <memory>


class EnemySeparation
{
public:

    static void Resolve(
        std::vector<std::unique_ptr<Enemy>>& enemies
    );

};