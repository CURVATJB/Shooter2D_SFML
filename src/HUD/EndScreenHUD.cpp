#include "HUD/EndScreenHUD.h"
#include "GameWindow.h"
#include "Components/RenderHandler.h"
#include "Managers/ScoreManager.h"

void EndScreenHUD::Activate(sf::Vector2f position, sf::Vector2f offsetPos, float scale, float rotation)
{
	const auto score = "FIN DU JEU \nMerci d'avoir joué ! \nVotre score est " + std::to_string(ScoreManager::GetScore());
	SetRenderHandler(score, "EndText", 3, sf::Vector2f(GameWindow::m_sizeWindow.x / 2 - 200, GameWindow::m_sizeWindow.y / 2-200));
	GetRenderHandler()->AddText("appuyez sur R pour redémarrer", "Restar", 3, sf::Vector2f(GameWindow::m_sizeWindow.x / 2 - 200, GameWindow::m_sizeWindow.y / 2-100));
}
