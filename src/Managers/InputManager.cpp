#include "Managers/InputManager.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "GameLoop.h"
#include "GameWindow.h"


void InputManager::HandleInputs()
{
    sf::Event Events;

    while (GameWindow::m_window->pollEvent(Events))
    {
        if (Events.type == sf::Event::Closed)
        {
            GameWindow::m_window->close();
        }

        // catch the resize Events
        if (Events.type == sf::Event::Resized)
        {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, static_cast<float>(Events.size.width), static_cast<float>(Events.size.height));
            GameWindow::m_window->setView(sf::View(visibleArea));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        GameWindow::m_window->close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        //si on est bien mort
        if(GameWindow::GetGameLevel()->m_player == nullptr)
        {
            GameLoop::GetInstance()->StartGame();
        }
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
        || sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        SendSignalIfNewInput(m_shoot, true);
    }
    else
    {
        SendSignalIfNewInput(m_shoot, false);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        SendSignalIfNewInput(m_forward, true);
    }
    else
    {
        SendSignalIfNewInput(m_forward, false);
    }


    // DEBUG
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
    {
        SendSignalIfNewInput(m_debugNum1, true);
    }
    else
    {
        SendSignalIfNewInput(m_debugNum1, false);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
    {
        SendSignalIfNewInput(m_debugNum2, true);
    }
    else
    {
        SendSignalIfNewInput(m_debugNum2, false);
    }

    
}

void InputManager::SendSignalIfNewInput(InputMapping& input, bool pressed)
{
    if (pressed && !input.second)
    {
        input.second = true;
        m_inputSignal(input);
    }
    if (!pressed && input.second)
    {
        input.second = false;
        m_inputSignal(input);
    }
}
