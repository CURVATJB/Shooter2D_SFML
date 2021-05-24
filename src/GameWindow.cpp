#include "GameWindow.h"
#include <SFML/Graphics/RenderWindow.hpp>

bool GameWindow::CheckIfInsideWindow(GameObject* gameObject)
{
	if (gameObject->m_position.x < 0
		|| gameObject->m_position.y < 0
		|| gameObject->m_position.x > m_window->getSize().x
		|| gameObject->m_position.y > m_window->getSize().y)
	{
		return false;
	}
	return true;
}