#include "Components/LifeComponent.h"
#include "GameWindow.h"
#include "GameObjects/GameObject.h"
#include "Tools/Print.h"

void LifeComponent::TickComponent(int64_t deltaTime)
{
    if(m_timer < m_collisionDamageCooldown * 1000000)
    {
        m_timer += deltaTime;
    }else
    {
        m_canTakeDamageOnCollision = true;
    }
}

void LifeComponent::ModifyHealth(float modification)
{
    m_currentHealth += modification;

    //clamp de la vie
    if(m_currentHealth > m_maxHealth)
        m_currentHealth = m_maxHealth;

    if(m_currentHealth <= 0)
    {
        Print::PrintLog(typeid(*m_owner).name()," is dead ! ");
        
        m_currentHealth = 0;
        m_owner->Deactivate();
    }
    // Print::PrintLog("modified health, new life is : ",m_currentHealth);
}

void LifeComponent::CollisionDamage(float damageOnCollision)
{
    if(m_canTakeDamageOnCollision)
    {
        ModifyHealth(-damageOnCollision);
        m_timer = 0;
        m_canTakeDamageOnCollision = false;
    }
}


