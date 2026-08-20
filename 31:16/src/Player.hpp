#pragma once

#include "Actor.hpp"
#include "Weapon.hpp"
#include "WeaponType.hpp"
#include "GameContext.hpp"
#include <memory>
#include <vector>


class Player : public Actor
{
public:

    Player(Vector2 position);

    void Update(float dt) override;

    void UpdateWeapons(float dt,Vector2 mousePosition, GameContext& context);

    void Draw() const override;

    bool TryTakeDamage(int amount);

    bool UnlockWeapon(WeaponType type);

    
    
    void AddWeapon(std::unique_ptr<Weapon> weapon);

    bool HasWeapon(WeaponType type) const;
 
    bool CanUpgradeWeapon(WeaponType type) const;

    int GetWeaponLevel(WeaponType type) const;

    const char* GetWeaponDisplayName(WeaponType type) const;

    const char* GetWeaponUpgradeName(WeaponType type) const;

    const char* GetWeaponUpgradeDescription(WeaponType type) const;


    void UpgradeWeapon(WeaponType type);
        

private:

    Weapon* FindWeapon(WeaponType type);

    const Weapon* FindWeapon(WeaponType type) const;

    std::vector<std::unique_ptr<Weapon>> m_weapons;

    std::vector<WeaponType> m_unlockedWeapons;

    float m_speed;

    float m_damageCooldown;

};


