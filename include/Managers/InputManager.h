#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Signal.h"

//une enum pour 
enum class InputsEnum
{
	Shoot,
	Forward,
	DebugNum1,
	DebugNum2,
};

typedef std::pair<InputsEnum, bool> InputMapping;

class InputManager
{
public:

	~InputManager() = default;

	//appelé à chaque tick, check les inputs clavier
	static void HandleInputs();

	//si un input change par rapport à sa valeur actuelle, on émet un signal
	static void SendSignalIfNewInput(InputMapping& input, bool pressed);

	//donne le signal émit par cette classe
	static Signal<InputMapping>& GetSignal()
	{
		return m_inputSignal;
	}

public:
	//le signal émit
	inline static Signal<InputMapping> m_inputSignal;

private:
	InputManager() = default;

private:
	//nos inputs et leurs valeures 
	inline static InputMapping m_shoot = std::make_pair(InputsEnum::Shoot, false);
	inline static InputMapping m_forward = std::make_pair(InputsEnum::Forward, false);
	inline static InputMapping m_debugNum1 = std::make_pair(InputsEnum::DebugNum1, false);
	inline static InputMapping m_debugNum2 = std::make_pair(InputsEnum::DebugNum2, false);
};

#endif
