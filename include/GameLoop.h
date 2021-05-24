#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "Singleton.h"

class GameLevel;

namespace sf
{
	class Clock;
	class RenderWindow;
}

class GameLoop : public Singleton<GameLoop>
{
	friend class Singleton<GameLoop>;

public:
	void StartGame();

	bool m_gameIsPlaying = true;

	~GameLoop() = default;

private:
	GameLoop();

	//update all game objects
	void _Update();
	//after all updates, one render
	void _Render() const;

private:
	//temps entre chaque frame
	int64_t m_deltaTime = 0; //en microsecondes !
	int m_updateTime = 0;//temps pour faire toutes les boucles updates avant un rendu
	int m_updateSurplus = 0;//temps pour faire toutes les boucles updates avant un rendu
	float m_targetFPS = 60.0f;

	GameLevel* m_gameLevel = nullptr;
};
#endif
