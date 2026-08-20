#include "EnemySeparation.hpp"

#include <cmath>


namespace
{
    constexpr float MIN_DISTANCE_SQUARED =
        0.0001f;
}


void EnemySeparation::Resolve(
    std::vector<std::unique_ptr<Enemy>>& enemies
)
{
    for (size_t i = 0;
         i < enemies.size();
         ++i)
    {
        for (size_t j = i + 1;
             j < enemies.size();
             ++j)
        {
            Enemy& a =
                *enemies[i];


            Enemy& b =
                *enemies[j];


            Vector2 difference =
            {
                a.GetPosition().x -
                    b.GetPosition().x,

                a.GetPosition().y -
                    b.GetPosition().y
            };


            float minimumDistance =
                a.GetRadius() +
                b.GetRadius();


            float distanceSquared =
                difference.x *
                difference.x +

                difference.y *
                difference.y;


            if (
                distanceSquared >=
                minimumDistance *
                minimumDistance
            )
            {
                continue;
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


            // Each enemy moves half of
            // the penetration distance.
            float correction =
                overlap *
                0.5f;


            a.Translate(
                {
                    direction.x *
                        correction,

                    direction.y *
                        correction
                }
            );


            b.Translate(
                {
                    -direction.x *
                        correction,

                    -direction.y *
                        correction
                }
            );
        }
    }
}