#pragma once

#include "raylib.h"


namespace WeaponDraw
{

void DrawJalurGemilangSlash(
    Vector2 position,
    float rotation,
    float scale
);


void DrawRotiCanai(
    Vector2 position,
    Vector2 direction,
    float scale
);


void DrawFireworkLauncher(
    Vector2 position,
    Vector2 direction,
    float scale
);


void DrawTehTarikBeam(
    Vector2 start,
    Vector2 end,
    float alpha
);


void DrawDurianAura(
    Vector2 position,
    float radius,
    float alpha
);

}