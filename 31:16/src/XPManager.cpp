#include "XPManager.hpp"

#include "XPOrb.hpp"

#include "Collision.hpp"
#include "Entity.hpp"
#include "GameAudio.hpp"

#include <algorithm>


void XPManager::Spawn(Vector2 position, int value)
{
    m_orbs.push_back(std::make_unique<XPOrb>(position, value));

    GameAudio::PlayXPDrop();
}


int XPManager::Update(float dt, const Entity& player)
{
    int collectedXP = 0;


    for (auto& orb : m_orbs)
    {
        orb->Update(dt);
    }


    m_orbs.erase(
        std::remove_if(
            m_orbs.begin(),
            m_orbs.end(),

            [&player, &collectedXP](const std::unique_ptr<XPOrb>& orb)
            {
                if (!Collision::Check(*orb, player))
                {
                    return false;
                }

                collectedXP += orb->GetValue();

                return true;
            }
        ),

        m_orbs.end()
    );


    if (collectedXP > 0)
    {
        GameAudio::PlayXPPickup();
    }


    return collectedXP;
}


void XPManager::Draw() const
{
    for (const auto& orb : m_orbs)
    {
        orb->Draw();
    }
}