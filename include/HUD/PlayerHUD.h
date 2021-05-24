#ifndef PLAYERHUD_H
#define PLAYERHUD_H

#include <SFML/Graphics/Text.hpp>
#include "GameObjects/GameObject.h"
#include "Managers/ScoreManager.h"

namespace sf {
	class Sprite;
}

class Player;

class PlayerHUD : public GameObject
{
public:

	PlayerHUD() = default;
	~PlayerHUD() override = default;

	void Activate(sf::Vector2f position = sf::Vector2f(0.f, 0.f), sf::Vector2f offsetPos = sf::Vector2f(0.f, 0.f), float scale = 1.f, float rotation = 0.f) override;

	void Deactivate() override
	{
		GameObject::Deactivate();

		m_deltatimeText = nullptr;
		ScoreManager::GetSignal().Disconnect(m_signalID);
	}

	void Tick(int64_t deltaTime) override;

public:
	sf::Text* m_deltatimeText = nullptr;


private:
	void _HandleChangeScore(int score) const;

private:
	sf::Sprite* m_healthBar = nullptr;
	int m_signalID = 0;
};

#endif //PlayerHUD_H