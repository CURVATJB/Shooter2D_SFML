#ifndef ENEMY_H
#define ENEMY_H

#include "GameObjects/Character.h"

class EnemySpawner;

class Enemy : public Character
{
public:
	Enemy() = default;
	~Enemy() override = default;

	void Tick(int64_t deltaTime) override;

	virtual void Activate(sf::Vector2f position = sf::Vector2f(0.f, 0.f), sf::Vector2f offsetPos = sf::Vector2f(0.f, 0.f), float scale = 1.f, float rotation = 0.f) override;
	void Deactivate() override;

	TypeId GetTypeId() override { return GetClassTypeId(); }
	static TypeId GetClassTypeId() { return "Enemy"; }


	EnemySpawner* m_enemySpawner = nullptr;

private:
	float m_enemyMaxHealth = 3.f;

};
#endif //ENEMY_H