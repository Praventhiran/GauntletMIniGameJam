#pragma once

#include "raylib.h"


namespace GameText
{
    void Draw(
        const char* text,
        Vector2 position,
        float fontSize,
        Color color,
        float spacing = 1.0f
    );


    Vector2 Measure(
        const char* text,
        float fontSize,
        float spacing = 1.0f
    );
}