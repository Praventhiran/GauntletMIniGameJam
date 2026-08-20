#include "Player.hpp"
#include "GameText.hpp"
#include "BasicGunWeapon.hpp"
#include "BoomerangWeapon.hpp"
#include "SwordWeapon.hpp"
#include "BeamWeapon.hpp"
#include "AuraWeapon.hpp"
#include "Weapon.hpp"
#include <cmath>
#include <memory>
#include <vector>


namespace
{
    constexpr float PLAYER_DAMAGE_COOLDOWN = 0.75f;
}

Player::Player(Vector2 position)
    : Actor(position, 100), 
    m_speed(300.0f),
    m_damageCooldown(0.0f)
    
{
    m_weapons.push_back(std::make_unique<SwordWeapon>());
    m_weapons.push_back(std::make_unique<AuraWeapon>());
    m_weapons.push_back(std::make_unique<BeamWeapon>());
    m_weapons.push_back(std::make_unique<BasicGunWeapon>());
    m_weapons.push_back(std::make_unique<BoomerangWeapon>());

}

void Player::Update(float dt)
{
    // Update damage invulnerability timer.
    if (m_damageCooldown > 0.0f)
    {
        m_damageCooldown -= dt;

        if (m_damageCooldown < 0.0f)
        {
            m_damageCooldown = 0.0f;
        }
    }


    // Dead players cannot move.
    if (IsDead())
    {
        return;
    }


    Vector2 movement = { 0.0f, 0.0f };


    if (IsKeyDown(KEY_W))
    {
        movement.y -= 1.0f;
    }

    if (IsKeyDown(KEY_S))
    {
        movement.y += 1.0f;
    }

    if (IsKeyDown(KEY_A))
    {
        movement.x -= 1.0f;
    }

    if (IsKeyDown(KEY_D))
    {
        movement.x += 1.0f;
    }


    // Normalize movement so diagonal movement
    // is not faster than horizontal/vertical movement.
    float lengthSquared =
        movement.x * movement.x +
        movement.y * movement.y;


    if (lengthSquared > 0.0f)
    {
        float length = std::sqrt(lengthSquared);

        movement.x /= length;
        movement.y /= length;


        m_position.x += movement.x * m_speed * dt;
        m_position.y += movement.y * m_speed * dt;
    }
}


void Player::AddWeapon(std::unique_ptr<Weapon> weapon)
{
    if (!weapon)
    {
        return;
    }


    if (HasWeapon(weapon->GetType()))
    {
        return;
    }


    m_weapons.push_back(std::move(weapon));
}

    




void Player::UpdateWeapons(float dt, Vector2 mousePosition, GameContext& context)
{
    if (IsDead())
    {
        return;
    }


    for (auto& weapon : m_weapons)
    {
        weapon->Update(
            dt,
            m_position,
            mousePosition,
            context
        );
    }
}


bool Player::TryTakeDamage(int amount)
{
    // Player is currently invulnerable.
    if (m_damageCooldown > 0.0f)
    {
        return false;
    }


    if (IsDead())
    {
        return false;
    }


    TakeDamage(amount);

    m_damageCooldown = PLAYER_DAMAGE_COOLDOWN;

    return true;
}



bool Player::HasWeapon(WeaponType type) const
{
    return FindWeapon(type) != nullptr;
}


bool Player::CanUpgradeWeapon(WeaponType type) const
{
    const Weapon* weapon = FindWeapon(type);


    if (weapon == nullptr)
    {
        return false;
    }


    return weapon->CanUpgrade();
}


int Player::GetWeaponLevel(WeaponType type) const
{
    const Weapon* weapon = FindWeapon(type);


    if (weapon == nullptr)
    {
        return 0;
    }


    return weapon->GetLevel();
}


const char* Player::GetWeaponDisplayName(WeaponType type) const
{
    const Weapon* weapon = FindWeapon(type);


    if (weapon == nullptr)
    {
        return "";
    }


    return weapon->GetDisplayName();
}


const char* Player::GetWeaponUpgradeName(WeaponType type) const
{
    const Weapon* weapon = FindWeapon(type);


    if (weapon == nullptr)
    {
        return "";
    }


    return weapon->GetUpgradeName();
}


const char* Player::GetWeaponUpgradeDescription(WeaponType type) const
{
    const Weapon* weapon = FindWeapon(type);


    if (weapon == nullptr)
    {
        return "";
    }


    return weapon->GetUpgradeDescription();
}


void Player::UpgradeWeapon(WeaponType type)
{
    Weapon* weapon = FindWeapon(type);


    if (weapon == nullptr)
    {
        return;
    }


    weapon->Upgrade();
}


Weapon* Player::FindWeapon(WeaponType type)
{
    for (auto& weapon : m_weapons)
    {
        if (weapon->GetType() == type)
        {
            return weapon.get();
        }
    }


    return nullptr;
}


const Weapon* Player::FindWeapon(WeaponType type) const
{
    for (const auto& weapon : m_weapons)
    {
        if (weapon->GetType() == type)
        {
            return weapon.get();
        }
    }


    return nullptr;
}



void Player::Draw() const
{
    DrawCircle(
        static_cast<int>(m_position.x),
        static_cast<int>(m_position.y),
        20.0f,
        WHITE
    );


    GameText::Draw(
        "PLAYER",
        {
            m_position.x - 40.0f,
            m_position.y - 45.0f
        },
        20.0f,
        WHITE
    );
}
 