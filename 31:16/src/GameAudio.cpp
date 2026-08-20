#include "GameAudio.hpp"

#include "raylib.h"


namespace
{
    Sound g_playerHitSound {};
    Sound g_levelUpSound {};
    Sound g_menuSelectSound {};

    Sound g_menuScrollSound {};
    Sound g_xpDropSound {};
    Sound g_xpPickupSound {};


    bool g_playerHitLoaded = false;
    bool g_levelUpLoaded = false;
    bool g_menuSelectLoaded = false;

    bool g_menuScrollLoaded = false;
    bool g_xpDropLoaded = false;
    bool g_xpPickupLoaded = false;


    void LoadOptionalSound(
        Sound& sound,
        bool& loaded,
        const char* path,
        float volume
    )
    {
        if (!FileExists(path))
        {
            return;
        }

        sound = LoadSound(path);
        SetSoundVolume(sound, volume);

        loaded = true;
    }


    void UnloadOptionalSound(
        Sound& sound,
        bool& loaded
    )
    {
        if (!loaded)
        {
            return;
        }

        UnloadSound(sound);

        loaded = false;
    }
}


void GameAudio::Load()
{
    InitAudioDevice();


    if (!IsAudioDeviceReady())
    {
        return;
    }


    LoadOptionalSound(
        g_playerHitSound,
        g_playerHitLoaded,
        "assets/sounds/player_hit.wav",
        0.7f
    );


    LoadOptionalSound(
        g_levelUpSound,
        g_levelUpLoaded,
        "assets/sounds/level_up.wav",
        0.8f
    );


    LoadOptionalSound(
        g_menuSelectSound,
        g_menuSelectLoaded,
        "assets/sounds/menu_select.wav",
        0.8f
    );


    LoadOptionalSound(
        g_menuScrollSound,
        g_menuScrollLoaded,
        "assets/sounds/scroll.wav",
        0.65f
    );


    LoadOptionalSound(
        g_xpDropSound,
        g_xpDropLoaded,
        "assets/sounds/xp_drop.wav",
        0.55f
    );


    LoadOptionalSound(
        g_xpPickupSound,
        g_xpPickupLoaded,
        "assets/sounds/xp_pickup.wav",
        0.65f
    );
}


void GameAudio::PlayPlayerHit()
{
    if (g_playerHitLoaded)
    {
        PlaySound(g_playerHitSound);
    }
}


void GameAudio::PlayLevelUp()
{
    if (g_levelUpLoaded)
    {
        PlaySound(g_levelUpSound);
    }
}


void GameAudio::PlayMenuSelect()
{
    if (g_menuSelectLoaded)
    {
        PlaySound(g_menuSelectSound);
    }
}


void GameAudio::PlayMenuScroll()
{
    if (g_menuScrollLoaded)
    {
        PlaySound(g_menuScrollSound);
    }
}


void GameAudio::PlayXPDrop()
{
    if (g_xpDropLoaded)
    {
        PlaySound(g_xpDropSound);
    }
}


void GameAudio::PlayXPPickup()
{
    if (g_xpPickupLoaded)
    {
        PlaySound(g_xpPickupSound);
    }
}


void GameAudio::Unload()
{
    UnloadOptionalSound(g_playerHitSound, g_playerHitLoaded);
    UnloadOptionalSound(g_levelUpSound, g_levelUpLoaded);
    UnloadOptionalSound(g_menuSelectSound, g_menuSelectLoaded);

    UnloadOptionalSound(g_menuScrollSound, g_menuScrollLoaded);
    UnloadOptionalSound(g_xpDropSound, g_xpDropLoaded);
    UnloadOptionalSound(g_xpPickupSound, g_xpPickupLoaded);


    if (IsAudioDeviceReady())
    {
        CloseAudioDevice();
    }
}