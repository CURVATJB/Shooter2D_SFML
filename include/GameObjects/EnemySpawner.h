#ifndef SPAWNER_H
#define SPAWNER_H

#include "GameObjects/GameObject.h"

class Enemy;

class EnemySpawner : public GameObject
{

public:

	EnemySpawner() = default;
	~EnemySpawner() override = default;

	void Activate(sf::Vector2f position = sf::Vector2f(0.f, 0.f), sf::Vector2f offsetPos = sf::Vector2f(0.f, 0.f), float scale = 1.f, float rotation = 0.f) override
	{
		GameObject::Activate(position, offsetPos, scale, rotation);
	}

	void Deactivate() override
	{
		GameObject::Deactivate();
	}

	void Tick(int64_t deltaTime) override;

	void DoSpawn(float lifeMultiply);
	void RandomLocation(Enemy* EnemytoSpawn);
	void RandomMovement(Enemy* EnemytoSpawn);
	void RandomShoot(Enemy* EnemytoSpawn);

	std::list<Enemy*> m_EnemyList;
	int m_maxEnnemy = 1;
	int m_nbEnemyEliminated = 0;
	int m_targetKills = 2;
	float m_lifeMultiply = 1.f;

	int64_t m_timer = 0;
	bool m_canSpawn = true;
};

#endif //SPAWNER_H