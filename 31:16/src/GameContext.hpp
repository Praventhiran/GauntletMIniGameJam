#pragma once


class ProjectileManager;
class MeleeManager;


struct GameContext
{
    ProjectileManager& projectileManager;

    MeleeManager& meleeManager;
};