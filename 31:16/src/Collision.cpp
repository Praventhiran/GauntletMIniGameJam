#include "Collision.hpp"

#include <cmath>


namespace
{
    constexpr float MIN_DISTANCE_SQUARED =
        0.0001f;
}


bool Collision::Check(
    const Entity& a,
    const Entity& b
)
{
    Vector2 positionA =
        a.GetPosition();


    Vector2 positionB =
        b.GetPosition();


    float dx =
        positionA.x -
        positionB.x;


    float dy =
        positionA.y -
        positionB.y;


    float distanceSquared =
        dx * dx +
        dy * dy;


    float combinedRadius =
        a.GetRadius() +
        b.GetRadius();


    return
        distanceSquared <
        combinedRadius *
        combinedRadius;
}


bool Collision::ResolveOverlap(
    Entity& movable,
    const Entity& fixed
)
{
    Vector2 movablePosition =
        movable.GetPosition();


    Vector2 fixedPosition =
        fixed.GetPosition();


    Vector2 difference =
    {
        movablePosition.x -
            fixedPosition.x,

        movablePosition.y -
            fixedPosition.y
    };


    float distanceSquared =
        difference.x *
        difference.x +

        difference.y *
        difference.y;


    float minimumDistance =
        movable.GetRadius() +
        fixed.GetRadius();


    if (
        distanceSquared >=
        minimumDistance *
        minimumDistance
    )
    {
        return false;
    }


    Vector2 direction;

    float distance;


    if (
        distanceSquared <=
        MIN_DISTANCE_SQUARED
    )
    {
        direction =
        {
            1.0f,
            0.0f
        };


        distance =
            0.0f;
    }
    else
    {
        distance =
            std::sqrt(
                distanceSquared
            );


        direction =
        {
            difference.x /
                distance,

            difference.y /
                distance
        };
    }


    float overlap =
        minimumDistance -
        distance;


    movable.Translate(
        {
            direction.x *
                overlap,

            direction.y *
                overlap
        }
    );


    return true;
}