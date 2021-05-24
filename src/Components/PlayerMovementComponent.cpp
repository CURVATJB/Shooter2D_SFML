#include "Components/PlayerMovementComponent.h"
#include <Tools/VectorTools.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameWindow.h"
#include "GameObjects/GameObject.h"
#include "Tools/SMath.h"


PlayerMovementComponent::PlayerMovementComponent()
{
	m_maxVelocity = 0.0004f;
	InputManager::GetSignal().Connect<PlayerMovementComponent>(this, &PlayerMovementComponent::OnInputChanged);
}

void PlayerMovementComponent::TickComponent(int64_t deltaTime)
{
	const auto MousePos = GameWindow::m_cursorPos;
	const auto Pos = m_owner->m_position;

	//distance vers la souris
	const auto DeltaPosX = MousePos.x - (Pos.x + m_owner->m_offsetPos.x);
	const auto DeltaPosY = MousePos.y - (Pos.y + m_owner->m_offsetPos.y);

	//on normalise cette distance
	const sf::Vector2f normDelta = VectorTools::NormaliseVector(sf::Vector2f(DeltaPosX, DeltaPosY));

	//rotation pour se tourner vers la souris
	const auto rot = std::atan2(DeltaPosY, DeltaPosX) * 180.f / PI;
	m_owner->m_rotation = rot + m_offsetAngle;

	//si on veut avancer
	if (m_moveTowardMouse)
	{
		//avant d'appliquer directement l'input, on va tester cette acceleration
		sf::Vector2f Acceleration = m_inertia;
		Acceleration.x += normDelta.x * GetSpeed() * static_cast<float>(deltaTime) * 0.0001f;
		Acceleration.y += normDelta.y * GetSpeed() * static_cast<float>(deltaTime) * 0.0001f;

		//ton vérifie que l'acceleration ne sera pas trop grande avant de l'appliquer
		if (VectorTools::Length(Acceleration) < GetMaxVelocity())
		{
			m_inertia = Acceleration;
		}
	}

	//la force de ralentissement
	const auto DragForce = 1 - (m_drag * (static_cast<float>(deltaTime) / 1000.f));

	//on applique cette force, proche de 0,999
	m_inertia *= DragForce;

	//on set la position, toujours en fonction du deltatime
	m_owner->m_position = Pos + (m_inertia * (static_cast<float>(deltaTime)));


	/*
	 * Check for side wrap of the player's position. TP from one side of the window to the other
	 */

	auto* Window = GameWindow::m_window;

	const auto LeftBorder = 0.f;
	const auto TopBorder = 0.f;
	const auto RightBorder = LeftBorder + Window->getSize().x;
	const auto BottomBorder = TopBorder + Window->getSize().y;

	//si on est trop à gauche on TP à droite
	if (m_owner->m_position.x < LeftBorder)
	{
		m_owner->m_position.x = RightBorder;
	}
	else if (m_owner->m_position.x > RightBorder)
	{
		m_owner->m_position.x = LeftBorder;
	}
	if (m_owner->m_position.y < TopBorder)
	{
		m_owner->m_position.y = BottomBorder;
	}
	else if (m_owner->m_position.y > BottomBorder)
	{
		m_owner->m_position.y = TopBorder;
	}
}

void PlayerMovementComponent::OnInputChanged(const InputMapping input)
{
	//si on a appuyé ou relaché la touche pour bouger
	if (input.first == InputsEnum::Forward)
	{
		// Print::PrintLog("pressed forward : ",input.second);
		m_moveTowardMouse = input.second;
	}
}
