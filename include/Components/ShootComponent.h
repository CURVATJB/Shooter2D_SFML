#ifndef SHOOTCOMPONENT_H
#define SHOOTCOMPONENT_H

#include <cstdint>
#include "Component.h"

class Character;

class ShootComponent : public Component
{
public:
    ShootComponent() = default;
    
    virtual ~ShootComponent() override = default;

    ShootComponent(ShootComponent& shootComponent) :
        m_additionnalShootNumber(shootComponent.m_additionnalShootNumber),
        m_fireRateModifier(shootComponent.m_fireRateModifier),
        m_baseVelocityMultiplier(shootComponent.m_baseVelocityMultiplier)
    
    {
    }


    //gestion du délai entre les tirs
    virtual void TickComponent(int64_t deltaTime = 0) override;

    //on tire, overridé par les classes enfant
    virtual void ShootBullet(int initialAngle) = 0;
    //fonction overridée par les components enfant en fonction des spécificités de chaque arme
    virtual float GetWeaponFireRate() const { return 1; }
    virtual float GetWeaponShootNumber() const { return 1; }

    float GetFireRate()
    {
        return m_baseFireRate * m_fireRateModifier;
    }

    int GetShootNumber()
    {
        return m_baseShootNumber + m_additionnalShootNumber;
    }

public:
    //modifiées par les amélioration globales de partie, sont indépendantes des armes récupérées
    int m_baseShootNumber = 1; //nombre de tir quand on shoot, doit être incrémenté de 2 en 2
    int m_additionnalShootNumber = 0;
	float m_range = 0.f;//portée du tir 

    float m_baseFireRate = 2.f; //vitesse de tir, plus c'est petit plus on tire souvent
    float m_fireRateModifier = 1;

    int m_baseDispersion = 15; //angle
    float m_baseDamageMultiplier = 1.f; //TODO

    float m_baseVelocityMultiplier = 1.f; //TODO

    bool m_wantToShoot = false;

private:
    float m_timer = 0;
};
#endif //SHOOTCOMPONENT_H
