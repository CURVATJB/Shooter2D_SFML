#include "Components/ClassicPistol.h"
#include "GameWindow.h"
#include "StaticData.h"
#include "GameObjects/Bullet.h"
#include "Managers/AudioManager.h"
#include "Components/CollisionHandler.h"
#include "GameObjects/Player.h"

ClassicPistol::ClassicPistol()
{
	m_baseShootNumber = 1;
	m_baseFireRate = 5.f;
	m_baseDispersion = 15;
	m_range = 5000.f;
}

void ClassicPistol::ShootBullet(const int initialAngle)
{
	auto* NewBullet = GameWindow::GetGameLevel()->SpawnActor<Bullet>(0.f, m_owner->m_position, m_owner->m_rotation + static_cast<float>(initialAngle));
	CollisionType ColType;
	std::vector<CollisionType> ExcludeColType;
	if (dynamic_cast<Player*>(m_owner))
	{
		ColType = CollisionType::PlayerProjectileChannel;
		ExcludeColType = std::vector<CollisionType>({ CollisionType::PlayerChannel, CollisionType::EnemyProjectileChannel, CollisionType::PlayerProjectileChannel });
	}
	else
	{
		ColType = CollisionType::EnemyProjectileChannel;
		ExcludeColType = std::vector<CollisionType>({ CollisionType::EnemyChannel, CollisionType::EnemyProjectileChannel, CollisionType::PlayerProjectileChannel });
	}
	NewBullet->SetCollisionHandler(ColType, StaticData::BulletCollision, 9.f, ExcludeColType);
	AudioManager::PlaySound(AudioManager::ESounds::FireBullet, 10);
}