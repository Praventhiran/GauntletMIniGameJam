#include "Weapon.hpp"


Weapon::Weapon(WeaponStats stats)
    : m_stats(stats),
      m_timer(0.0f),
      m_level(1)
{
}


int Weapon::GetLevel() const
{
    return m_level;
}


bool Weapon::CanUpgrade() const
{
    return m_level < MAX_LEVEL;
}


void Weapon::Upgrade()
{
    if (!CanUpgrade())
    {
        return;
    }


    m_level++;

    ApplyUpgrade(m_level);
}