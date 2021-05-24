#include "Components/Sniper.h"
#include "GameWindow.h"
#include "StaticData.h"
#include "Components/CollisionHandler.h"
#include "GameObjects/Bullet.h"
#include "Managers/AudioManager.h"
#include "GameObjects/Player.h"



void Sniper::ShootBullet(int initialAngle)
{
	auto* NewBullet = GameWindow::GetGameLevel()->SpawnActor<Bullet>(0.f, m_owner->m_position, m_owner->m_rotation + initialAngle, 10.f);
	CollisionType ColType;
	std::vector<CollisionType> ExcludeColType;
	if (dynamic_cast<Player*>(m_owner))
	{
		Print::PrintLog("player sniper bullet");
		ColType = CollisionType::PlayerProjectileChannel;
		ExcludeColType = std::vector<CollisionType>({ CollisionType::PlayerChannel, CollisionType::EnemyProjectileChannel, CollisionType::PlayerProjectileChannel });
	}
	else
	{
		Print::PrintLog("enemy sniper bullet");
		ColType = CollisionType::EnemyProjectileChannel;
		ExcludeColType = std::vector<CollisionType>({ CollisionType::EnemyChannel, CollisionType::EnemyProjectileChannel, CollisionType::PlayerProjectileChannel });
	}
	
	NewBullet->SetCollisionHandler(ColType, StaticData::BulletCollision, 9.f*10, ExcludeColType);
	AudioManager::PlaySound(AudioManager::ESounds::FireBullet, 10);
}
