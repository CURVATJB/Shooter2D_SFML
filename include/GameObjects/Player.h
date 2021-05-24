#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "HUD/PlayerHUD.h"
#include "Managers/InputManager.h"

class Player : public Character
{
public:

	Player() = default;
	~Player() override = default;
	void Tick(int64_t deltaTime) override;

	void Activate(sf::Vector2f position, sf::Vector2f offsetPos = sf::Vector2f(0.f, 0.f), float scale = 1.f, float rotation = 0.f) override;

	void Deactivate() override;

	//quand on détecte un changement d'input
	void OnInputChanged(InputMapping input) const;

	virtual TypeId GetTypeId() override { return GetClassTypeId(); }
	static TypeId GetClassTypeId() { return "Player"; }

private:
	PlayerHUD* m_hud = nullptr;
	int m_signalSlotID = 0;
};

#endif //PLAYER_H
