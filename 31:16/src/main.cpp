#include "raylib.h"

#include "GameFonts.hpp"
#include "GameText.hpp"
#include "GameAudio.hpp"

#include "GameState.hpp"
#include "WeaponType.hpp"

#include "Player.hpp"
#include "PlayerProgress.hpp"

#include "HealthBar.hpp"
#include "ExperienceBar.hpp"
#include "LevelUpMenu.hpp"

#include "EnemySpawner.hpp"

#include "ProjectileManager.hpp"
#include "MeleeManager.hpp"
#include "XPManager.hpp"

#include "GameContext.hpp"
#include "Collision.hpp"

#include "BoomerangWeapon.hpp"
#include "SwordWeapon.hpp"
#include "BeamWeapon.hpp"
#include "AuraWeapon.hpp"

#include <memory>
#include <optional>


namespace
{
    constexpr int SCREEN_WIDTH = 1280;
    constexpr int SCREEN_HEIGHT = 720;

    constexpr int ENEMY_CONTACT_DAMAGE = 10;


    void UnlockWeapon(Player& player, WeaponType type)
    {
        switch (type)
        {
            case WeaponType::Boomerang:
                player.AddWeapon(std::make_unique<BoomerangWeapon>());
                break;

            case WeaponType::Sword:
                player.AddWeapon(std::make_unique<SwordWeapon>());
                break;

            case WeaponType::Beam:
                player.AddWeapon(std::make_unique<BeamWeapon>());
                break;

            case WeaponType::Aura:
                player.AddWeapon(std::make_unique<AuraWeapon>());
                break;

            case WeaponType::BasicGun:
                break;
        }
    }
}


int main()
{
    // -------------------------
    // INITIALIZATION
    // -------------------------

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "31:16");

    GameFonts::Load();

    GameAudio::Load();

    SetTargetFPS(60);


    Player player(
        {
            SCREEN_WIDTH / 2.0f,
            SCREEN_HEIGHT / 2.0f
        }
    );


    PlayerProgress playerProgress;


    HealthBar healthBar(player.GetMaxHealth());

    ExperienceBar experienceBar;

    LevelUpMenu levelUpMenu;


    EnemySpawner enemySpawner;


    ProjectileManager projectileManager;

    MeleeManager meleeManager;

    XPManager xpManager;


    GameContext context
    {
        projectileManager,
        meleeManager
    };


    GameState gameState = GameState::Playing;


    int pendingLevelUps = 0;


    // -------------------------
    // GAME LOOP
    // -------------------------

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();


        // -------------------------
        // UI
        // -------------------------

        healthBar.Update(dt);

        experienceBar.Update(dt);


        // =========================
        // PLAYING
        // =========================

        if (gameState == GameState::Playing)
        {
            Vector2 mousePosition = GetMousePosition();


            // -------------------------
            // PLAYER
            // -------------------------

            player.Update(dt);

            player.UpdateWeapons(dt, mousePosition, context);


            // -------------------------
            // ENEMIES
            // -------------------------

            enemySpawner.Update(dt, player.GetPosition());


            // -------------------------
            // PROJECTILES
            // -------------------------

            projectileManager.Update(
                dt,
                enemySpawner.GetEnemies(),
                player.GetPosition()
            );


            // -------------------------
            // MELEE
            // -------------------------

            meleeManager.Update(
                dt,
                enemySpawner.GetEnemies(),
                player.GetPosition()
            );


            // -------------------------
            // DEAD ENEMIES DROP XP
            // -------------------------

            for (const auto& enemy : enemySpawner.GetEnemies())
            {
                if (enemy->IsDead())
                {
                    xpManager.Spawn(enemy->GetPosition(), 10);
                }
            }


            enemySpawner.RemoveDeadEnemies();


            // -------------------------
            // XP PICKUP
            // -------------------------

            int collectedXP = xpManager.Update(dt, player);


            if (collectedXP > 0)
            {
                experienceBar.OnXPCollected();

                int levelsGained = playerProgress.AddXP(collectedXP);


                if (levelsGained > 0)
                {
                    pendingLevelUps += levelsGained;

                    experienceBar.OnLevelUp();
                }
            }


            // -------------------------
            // ENEMY VS PLAYER
            // -------------------------

            for (auto& enemy : enemySpawner.GetEnemies())
            {
                if (Collision::Check(*enemy, player))
                {
                    bool tookDamage = player.TryTakeDamage(ENEMY_CONTACT_DAMAGE);


                    if (tookDamage)
                    {
                        healthBar.OnDamage();

                        GameAudio::PlayPlayerHit();
                    }


                    Collision::ResolveOverlap(*enemy, player);
                }
            }


            // -------------------------
            // STATE CHANGE
            // -------------------------

            if (player.IsDead())
            {
                gameState = GameState::GameOver;
            }
            else if (pendingLevelUps > 0)
            {
                if (levelUpMenu.HasAvailableWeapons())
                {
                    levelUpMenu.BuildChoices();

                    GameAudio::PlayLevelUp();

                    gameState = GameState::LevelUp;
                }
                else
                {
                    pendingLevelUps = 0;
                }
            }
        }


        // =========================
        // LEVEL UP
        // =========================

        else if (gameState == GameState::LevelUp)
        {
            std::optional<WeaponType> selectedWeapon = levelUpMenu.Update(dt);


            if (selectedWeapon.has_value())
            {
                GameAudio::PlayMenuSelect();


                UnlockWeapon(
                    player,
                    selectedWeapon.value()
                );


                levelUpMenu.MarkUnlocked(
                    selectedWeapon.value()
                );


                pendingLevelUps--;


                // -------------------------
                // ANOTHER LEVEL WAITING
                // -------------------------

                if (
                    pendingLevelUps > 0 &&
                    levelUpMenu.HasAvailableWeapons()
                )
                {
                    levelUpMenu.BuildChoices();

                    GameAudio::PlayLevelUp();

                    gameState = GameState::LevelUp;
                }
                else
                {
                    if (!levelUpMenu.HasAvailableWeapons())
                    {
                        pendingLevelUps = 0;
                    }


                    gameState = GameState::Playing;
                }
            }
        }


        // =========================
        // DRAW
        // =========================

        BeginDrawing();

        ClearBackground(DARKGRAY);


        // -------------------------
        // WORLD
        // -------------------------

        player.Draw();


        for (const auto& enemy : enemySpawner.GetEnemies())
        {
            enemy->Draw();
        }


        projectileManager.Draw();

        meleeManager.Draw();

        xpManager.Draw();


        // -------------------------
        // HUD
        // -------------------------

        healthBar.Draw(player.GetHealth());

        experienceBar.Draw(playerProgress.GetLevel(), playerProgress.GetCurrentXP(), playerProgress.GetXPToNextLevel());


        // -------------------------
        // LEVEL-UP SCREEN
        // -------------------------

        if (gameState == GameState::LevelUp)
        {
            DrawRectangle(
                0,
                0,
                GetScreenWidth(),
                GetScreenHeight(),
                Fade(BLACK, 0.72f)
            );


            levelUpMenu.Draw();
        }


        // -------------------------
        // GAME OVER
        // -------------------------

        if (gameState == GameState::GameOver)
        {
            DrawRectangle(
                0,
                0,
                GetScreenWidth(),
                GetScreenHeight(),
                Fade(BLACK, 0.55f)
            );


            const char* gameOverText = "GAME OVER";

            Vector2 gameOverSize = GameText::Measure(gameOverText, 60.0f);


            GameText::Draw(
                gameOverText,
                {
                    SCREEN_WIDTH / 2.0f - gameOverSize.x / 2.0f,
                    SCREEN_HEIGHT / 2.0f - gameOverSize.y / 2.0f
                },
                60.0f,
                RED
            );
        }


        EndDrawing();
    }


    // -------------------------
    // CLEANUP
    // -------------------------

    GameAudio::Unload();

    GameFonts::Unload();

    CloseWindow();


    return 0;
}