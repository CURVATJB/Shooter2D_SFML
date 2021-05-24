#include "HUD/PlayerHUD.h"

#include <SFML/Graphics/Text.hpp>

#include "GameWindow.h"
#include "Components/LifeComponent.h"
#include "Components/RenderHandler.h"
#include "GameObjects/Player.h"
#include "Managers/ScoreManager.h"
#include "Managers/TextureManager.h"

void PlayerHUD::Activate(sf::Vector2f position, sf::Vector2f offsetPos, float scale, float rotation)
{
	SetRenderHandler(TextureManager::GetTexturePtr(TextureManager::ETextures::HealthBarBG), "HealthBarBG", 3);
	GetRenderHandler()->AddSprite(TextureManager::GetTexturePtr(TextureManager::ETextures::HealthBar), "healthBar", 4);
	m_healthBar = GetRenderHandler()->GetRenderedItemWithKey<sf::Sprite>("healthBar");

	if (m_healthBar)
	{
		m_position = sf::Vector2f(GameWindow::m_sizeWindow.x / 2 - m_healthBar->getTexture()->getSize().x / 2, GameWindow::m_sizeWindow.y - 50);
	}

	GetRenderHandler()->AddText("0", "scoreText", 3, sf::Vector2f(GameWindow::m_sizeWindow.x - 100, 0));

	m_signalID = ScoreManager::GetSignal().Connect<PlayerHUD>(this, &PlayerHUD::_HandleChangeScore);

	GetRenderHandler()->AddText("deltatime : ","deltatimeText",3,sf::Vector2f(20,20),sf::Color::Cyan,15);
	m_deltatimeText = GetRenderHandler()->GetRenderedItemWithKey<sf::Text>("deltatimeText");
}

void PlayerHUD::Tick(int64_t deltaTime)
{
	GameObject::Tick(deltaTime);

	const auto* player = GameWindow::GetGameLevel()->m_player;
	if(player)
	{
		m_healthBar->setScale(player->m_lifeComponent->m_currentHealth / player->m_lifeComponent->m_maxHealth, 1);
	}
	std::string tmp = "deltatime : ";
	m_deltatimeText->setString(tmp.append(std::to_string(deltaTime)).append(" microsec"));
}

void PlayerHUD::_HandleChangeScore(const int score) const
{
	GetRenderHandler()->GetRenderedItemWithKey<sf::Text>("scoreText")->setString(std::to_string(score));
}
