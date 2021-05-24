#include "GameObjects/Enemy.h"
#include "GameLevel.h"
#include "GameObjects/Player.h"
#include "Components/RenderHandler.h"
#include "GameWindow.h"
#include "Tools/Print.h"
#include "Components/CollisionHandler.h"
#include "Managers/TextureManager.h"
#include "Components/IMovementComponent.h"
#include "StaticData.h"
#include "Components/LifeComponent.h"
#include "GameObjects/EnemySpawner.h"
#include "Managers/BonusSpawner.h"
#include "Managers/ScoreManager.h"
#include "Components/ShootComponent.h"

void Enemy::Tick(int64_t deltaTime)
{
    GameObject::Tick(deltaTime);

    if (m_movementComponent->m_distance <= GetShootComponent()->m_range)
    {
       GetShootComponent()->m_wantToShoot = true;	
    }
    else
    {        
       GetShootComponent()->m_wantToShoot = false;
    }

    GetComponentOfClass<LifeComponent>()->SetMaxHealth(m_enemyMaxHealth);
}

void Enemy::Activate(sf::Vector2f position, sf::Vector2f offsetPos, float scale, float rotation)
{
    Character::Activate(position, offsetPos, scale, rotation);
    //Au moment du spawn
    Print::PrintLog("here comes a new challenger");

    SetRenderHandler(TextureManager::GetTexturePtr(TextureManager::ETextures::ShipEnemy), "enemy", 1);

    auto Sprite = GetRenderHandler()->GetRenderedItemWithKey<sf::Sprite>("enemy");

    if (Sprite)
    {
        Sprite->setOrigin(sf::Vector2f(50.f, 50.f));
        Sprite->setScale(sf::Vector2f(1.f, 1.f));
    }

    SetCollisionHandler(CollisionType::EnemyChannel, StaticData::ShipCollision, 50, std::vector<CollisionType>({CollisionType::EnemyChannel, CollisionType::BonusChannel, CollisionType::EnemyProjectileChannel}));
}

void Enemy::Deactivate()
{
    Character::Deactivate();

    BonusSpawner::RollBonus(m_position);

    ScoreManager::ModifyScore(1); //une fa�on d'augmenter le score rapide mais on peut faire mieux

    m_enemySpawner->m_EnemyList.remove(this);

    m_enemySpawner->m_nbEnemyEliminated++;
}
