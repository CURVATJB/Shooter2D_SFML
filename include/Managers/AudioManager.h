#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H
#include <map>

namespace sf {
	class Music;
	class Sound;
	class SoundBuffer;
}

class AudioManager
{

public:
	//tous les sons
	enum class ESounds { FireBullet, EpicGameMusic };

	static void PlaySound(ESounds eSound, float volume = 20.f);

	static void PlayMusic(ESounds eSound);

	//retourne un pointeur vers la texture
	static sf::SoundBuffer* GetSoundPtr(ESounds eSound);

	~AudioManager();

public:
	//une map qui associe les textures chargées en mémoire à leur nom
	inline static std::map<ESounds, sf::SoundBuffer*> m_mapSons;  // NOLINT(clang-diagnostic-exit-time-destructors)
	static inline sf::Sound* m_soundPlayer = nullptr;
	static inline sf::Music* m_musicPlayer = nullptr;

private:
	//retourne le path associé à un nom de texture
	static const char* _GetPath(ESounds eSound);

	AudioManager() = default;
};

#endif //AUDIOMANAGER_H