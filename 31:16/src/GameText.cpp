#include "GameText.hpp"
#include "GameFonts.hpp"


void GameText::Draw(
    const char* text,
    Vector2 position,
    float fontSize,
    Color color,
    float spacing
)
{
    DrawTextEx(
        GameFonts::Bungee(),
        text,
        position,
        fontSize,
        spacing,
        color
    );
}


Vector2 GameText::Measure(
    const char* text,
    float fontSize,
    float spacing
)
{
    return MeasureTextEx(
        GameFonts::Bungee(),
        text,
        fontSize,
        spacing
    );
}