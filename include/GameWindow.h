#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <string>
#include <SFML/System/Vector2.hpp>
#include "GameLevel.h"
#include "Tools/Print.h"

namespace sf {
	class RenderWindow;
}

class GameWindow
{
public:
	
	static GameLevel* LoadGameLevel()
	{
		if(m_currentGameLevel != nullptr)
			delete m_currentGameLevel;
		
		m_currentGameLevel = new GameLevel();
		Print::PrintLog("game level created");
		m_currentGameLevel->SpawnGameObjects();

		return m_currentGameLevel;
	}

	static GameLevel* GetGameLevel()
	{
		return m_currentGameLevel;
	}

	//fonction utilitaire qui check si l'objet passé en paramètre est à l'intérieur de la fenêtre ou pas
	static bool CheckIfInsideWindow(GameObject* gameObject);

public:
	inline static sf::RenderWindow* m_window;
	inline static sf::Vector2f m_sizeWindow;
	inline static sf::Vector2i m_cursorPos;
	//global parameters
	inline static bool m_useFullscreen = true;
	inline static std::string m_gameName = "Shooter 2D SFML";  // NOLINT(clang-diagnostic-exit-time-destructors)

private:
	GameWindow() = default;
	
	inline static GameLevel* m_currentGameLevel;
};

#endif //GAMEWINDOW_H
