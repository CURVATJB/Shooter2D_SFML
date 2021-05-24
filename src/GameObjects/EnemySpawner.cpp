#include "GameObjects/EnemySpawner.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameWindow.h"
#include "GameLevel.h"
#include "GameObjects/Enemy.h"
#include "Components/KamikazeMovementComponent.h"
#include "Components/RunAwayMovementComponent.h"
#include "Components/ShotGun.h"
#include "Components/ClassicPistol.h"
#include "Components/LifeComponent.h"
#include "Components/Sniper.h"
#include "GameObjects/Character.h"

void EnemySpawner::Tick(int64_t deltaTime)
{
	m_timer += deltaTime;
	//Va faire le spawn d'un ennemi quand les conditions sont remplies
	if (m_timer >= 2000000 && m_EnemyList.size() != m_maxEnnemy)
	{
		m_timer = 0;
		DoSpawn(m_lifeMultiply);
		m_canSpawn = false;
	}

	//Gestion du changement de difficulté
	if (m_nbEnemyEliminated == m_targetKills)
	{
		m_nbEnemyEliminated = 0;
		m_targetKills = m_targetKills * 2;
		m_maxEnnemy += 2;
		m_lifeMultiply = m_lifeMultiply + 0.1f;
	}
}

void EnemySpawner::DoSpawn(float lifeMultiply)
{
	//Pour le spawn de l'ennemi
	auto* NewEnemy = GameWindow::GetGameLevel()->SpawnActor<Enemy>(sf::Vector2f(0.f, 0.f));
	RandomLocation(NewEnemy);
	RandomMovement(NewEnemy);
	RandomShoot(NewEnemy);
	NewEnemy->m_enemySpawner = this;
	m_EnemyList.push_back(NewEnemy);

	//Pour changer la quantité initiale de PV en fonction de la difficulté actuelle
	NewEnemy->m_lifeComponent->m_maxHealth = NewEnemy->m_lifeComponent->m_maxHealth * lifeMultiply;
	NewEnemy->m_lifeComponent->m_currentHealth = NewEnemy->m_lifeComponent->m_maxHealth;

}

void EnemySpawner::RandomLocation(Enemy* EnemytoSpawn)
{
	srand(time(0));

	const auto* window = GameWindow::m_window;
	const auto Side = std::rand() % 4;
	auto RandomX = 0;
	auto RandomY = 0;

	switch (Side)
	{
		//le Spawn se fera à gauche de l'écran
	case 0:
		RandomX = -1;
		RandomY = std::rand() % window->getSize().y + 1;
		break;

		//le spawn se fera à droite de l'écran
	case 1:
		RandomX = window->getSize().x + 1;
		RandomY = std::rand() % window->getSize().y + 1;
		break;
		//le spawn se fera en haut de l'écran
	case 2:
		RandomX = std::rand() % window->getSize().x + 1;
		RandomY = -1;
		break;

		//le spawn se fera en bas de l'écran
	case 3:
		RandomX = std::rand() % window->getSize().x + 1;
		RandomY = window->getSize().y + 1;
		break;
	default:
		break;
	}

	EnemytoSpawn->m_position = sf::Vector2f(static_cast<float>(RandomX), static_cast<float>(RandomY));
}

void EnemySpawner::RandomMovement(Enemy* EnemytoSpawn)
{
	srand(time(0));
	//va choisir une valeur aléatoire entre 0 et 1 (car 2 types de MovementComponents existants pour les ennemis)
	//et va attribuer au nouvel ennemi le MovementComponent correspondant
	const auto Random = std::rand() % 2;
	switch (Random)
	{
	case 0:
		EnemytoSpawn->m_movementComponent = new KamikazeMovementComponent();
		break;

	case 1:
		EnemytoSpawn->m_movementComponent = new RunAwayMovementComponent();
		break;
	default:
		break;
	}

	EnemytoSpawn->AddComponent(EnemytoSpawn->m_movementComponent);
}

void EnemySpawner::RandomShoot(Enemy* EnemytoSpawn)
{
	srand(time(0));
	//va choisir une valeur aléatoire entre 0 et 2 (car 3 types de ShootComponents existants)
	//et va attribuer au nouvel ennemi le ShootComponent correspondant
	const auto Random = std::rand() % 3;
	switch (Random)
	{
	case 0:
		EnemytoSpawn->SetShootComponent(new ClassicPistol());
		break;

	case 1:
		EnemytoSpawn->SetShootComponent(new ShotGun());
		break;

	case 2:
		EnemytoSpawn->SetShootComponent(new Sniper());
		break;
	default:
		break;
	}
}