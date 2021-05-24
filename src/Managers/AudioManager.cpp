#include "Managers/AudioManager.h"
#include <SFML/Audio.hpp>
#include "Tools/Print.h"

void AudioManager::PlaySound(const ESounds eSound, const float volume)
{
    if (m_soundPlayer == nullptr)
    {
        m_soundPlayer = new sf::Sound();
    }

    m_soundPlayer->setBuffer(*GetSoundPtr(eSound));
    m_soundPlayer->setVolume(volume);
    m_soundPlayer->play();
}

void AudioManager::PlayMusic(const ESounds eSound)
{
    if (m_musicPlayer == nullptr)
    {
        m_musicPlayer = new sf::Music;
    }

    if (!m_musicPlayer->openFromFile(_GetPath(eSound)))
    {
        return; // error
    }
    m_musicPlayer->setVolume(20);
    m_musicPlayer->setLoop(true);
    m_musicPlayer->play();

    Print::PrintLog("music playing");
}

const char* AudioManager::_GetPath(const ESounds eSound)
{
    switch (eSound)
    {
    case ESounds::FireBullet:
        return "../medias/Sons/sniper.wav";
    case ESounds::EpicGameMusic:
        return "../medias/Sons/Cjbeards - Fire And Thunder.wav";
    }
    return "error audio";
}

sf::SoundBuffer* AudioManager::GetSoundPtr(const ESounds eSound)
{
    const auto Iterator(m_mapSons.find(eSound));
    // Print::PrintLog("map size : ", mapTextures.size());

    //si on a notre texture de chargé
    if (Iterator != m_mapSons.end())
    {
        return Iterator->second;
    }
    //création d'un nouveau son
    auto* soundBuffer = new sf::SoundBuffer();
    soundBuffer->loadFromFile(_GetPath(eSound)); //on charge l'image voulue
    m_mapSons[eSound] = soundBuffer; //on conserve la donnée dans la map

    Print::PrintLog("create new sound ptr for ", _GetPath(eSound));

    return soundBuffer;
}

AudioManager::~AudioManager()
{
    if (m_soundPlayer != nullptr)
    {
        delete m_soundPlayer;
        m_soundPlayer = nullptr;
    }

    if (m_musicPlayer != nullptr)
    {
        delete m_musicPlayer;
        m_musicPlayer = nullptr;
    }

    for (auto pair : m_mapSons)
    {
        if (pair.second != nullptr)
        {
            delete pair.second;
            pair.second = nullptr;
        }
    }
}
