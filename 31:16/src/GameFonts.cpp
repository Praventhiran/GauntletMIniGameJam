#include "GameFonts.hpp"


namespace
{
    Font g_bungeeFont {};
}


void GameFonts::Load()
{
    g_bungeeFont = LoadFontEx(
        "assets/fonts/Bungee-Regular.ttf",
        64,
        nullptr,
        0
    );


    SetTextureFilter(
        g_bungeeFont.texture,
        TEXTURE_FILTER_BILINEAR
    );
}


void GameFonts::Unload()
{
    UnloadFont(
        g_bungeeFont
    );
}


const Font& GameFonts::Bungee()
{
    return g_bungeeFont;
}