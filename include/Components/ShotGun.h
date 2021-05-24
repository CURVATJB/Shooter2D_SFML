#ifndef SHOTGUN_H
#define SHOTGUN_H
#include "ShootComponent.h"

class ShotGun : public ShootComponent
{
public:
    ShotGun()
    {
        m_baseShootNumber = 5;
        m_baseFireRate = 10.f;
        m_baseDispersion = 10;
        m_range = 450.f;
    }

    explicit ShotGun(ShootComponent& shootComponent) : ShootComponent(shootComponent)
    {
        m_baseShootNumber = 5;
        m_baseFireRate = 10.f;
        m_baseDispersion = 10;
        m_range = 450.f;
    };

    void ShootBullet(int initialAngle) override;
};

#endif