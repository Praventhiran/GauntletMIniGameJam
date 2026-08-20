#include "WeaponDraw.hpp"

#include <cmath>


namespace WeaponDraw
{


    // =========================
    // Sword
    // =========================


    void DrawJalurGemilangSlash(
        Vector2 position,
        float rotation,
        float scale
    )
    {
        float length = 100.0f * scale;
        float width = 28.0f * scale;


        float radians =
            rotation * DEG2RAD;


        Vector2 direction =
        {
            std::cos(radians),
            std::sin(radians)
        };


        Vector2 perpendicular =
        {
            -direction.y,
            direction.x
        };


        // Sword points

        Vector2 base =
        {
            position.x,
            position.y
        };


        Vector2 top =
        {
            position.x +
                direction.x * length,

            position.y +
                direction.y * length
        };



        Vector2 p1 =
        {
            base.x +
                perpendicular.x * width,

            base.y +
                perpendicular.y * width
        };


        Vector2 p2 =
        {
            base.x -
                perpendicular.x * width,

            base.y -
                perpendicular.y * width
        };



        //
        // Glow
        //

        DrawTriangle(
            p1,
            p2,
            top,
            Fade(YELLOW,0.25f)
        );


        //
        // Blue Jalur Gemilang blade
        //

        DrawTriangle(
            p1,
            p2,
            top,
            BLUE
        );


        //
        // Malaysia stripes
        //

        for(int i = 1; i <= 4; i++)
        {
            float offset =
                -10.0f +
                i * 8.0f;


            Vector2 stripeStart =
            {
                base.x +
                    direction.x * 20 +
                    perpendicular.x * offset,

                base.y +
                    direction.y * 20 +
                    perpendicular.y * offset
            };


            Vector2 stripeEnd =
            {
                stripeStart.x +
                    direction.x * 65,

                stripeStart.y +
                    direction.y * 65
            };


            DrawLineEx(
                stripeStart,
                stripeEnd,
                4.0f * scale,
                i % 2 == 0 ? RED : WHITE
            );
        }


        //
        // Crescent
        //

        Vector2 emblem =
        {
            base.x +
                direction.x * 35,

            base.y +
                direction.y * 35
        };


        DrawCircle(
            emblem.x,
            emblem.y,
            9 * scale,
            YELLOW
        );


        DrawCircle(
            emblem.x +
                direction.x * 3,

            emblem.y +
                direction.y * 3,

            7 * scale,
            BLUE
        );


        //
        // Star
        //

        DrawPoly(
            {
                emblem.x +
                    direction.x * 12,

                emblem.y +
                    direction.y * 12
            },
            5,
            5 * scale,
            rotation,
            YELLOW
        );


        //
        // Handle
        //

        Vector2 handle =
        {
            base.x -
                direction.x * 8,

            base.y -
                direction.y * 8
        };


        DrawCircle(
            handle.x,
            handle.y,
            10 * scale,
            GOLD
        );


        DrawLineEx(
            handle,
            {
                handle.x -
                    direction.x * 20,

                handle.y -
                    direction.y * 20
            },
            8 * scale,
            DARKGRAY
        );
    }




    // =========================
    // FireworkGun
    // =========================

    void DrawFireworkLauncher(
        Vector2 position,
        Vector2 direction,
        float scale
    )
    {


        float angle =
            atan2(direction.y,direction.x)
            * RAD2DEG;


        Rectangle launcher =
        {
            position.x,
            position.y,
            45 * scale,
            15 * scale
        };


        DrawRectanglePro(
            launcher,
            {
                0,
                7 * scale
            },
            angle,
            RED
        );


        DrawCircle(
            position.x,
            position.y,
            8 * scale,
            YELLOW
        );


        Vector2 fire =
        {
            position.x - direction.x * 25,
            position.y - direction.y * 25
        };


        DrawCircle(
            fire.x,
            fire.y,
            6 * scale,
            ORANGE
        );
    }




    // =========================
    // RotiCanai
    // =========================

    void DrawRotiCanai(
        Vector2 position,
        Vector2 direction,
        float scale
    )
    {
 

        DrawCircleLines(
            position.x,
            position.y,
            25 * scale,
            BROWN
        );


        DrawLineEx(
            {
                position.x - direction.x * 15,
                position.y - direction.y * 15
            },
            {
                position.x + direction.x * 15,
                position.y + direction.y * 15
            },
            4 * scale,
            ORANGE
        );
    }



    // =========================
    // Beam
    // =========================

    void DrawTehTarikBeam(
        Vector2 start,
        Vector2 end,
        float opacity
    )
    {
        Color beam =
        {
            210,
            150,
            70,
            (unsigned char)(opacity * 255)
        };


        DrawLineEx(
            start,
            end,
            35,
            Fade(beam,opacity)
        );


        DrawLineEx(
            start,
            end,
            12,
            WHITE
        );
    }




    // =========================
    // Durian
    // =========================

    void DrawDurianAura(
        Vector2 position,
        float radius,
        float opacity
    )
    {
        Color green =
        {
            120,
            200,
            70,
            (unsigned char)(opacity * 255)
        };


        DrawCircleV(
            position,
            radius,
            Fade(green,opacity)
        );


        DrawCircleLines(
            position.x,
            position.y,
            radius,
            GREEN
        );
    }


}