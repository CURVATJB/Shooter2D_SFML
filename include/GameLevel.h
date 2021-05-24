#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <cstdint>
#include <list>
#include "Singleton.h"
#include "GameObjects/GameObject.h"
#include <cstdarg>

class Player;

namespace sf
{
    class RenderWindow;
}

class GameLevel
{
    friend class GameObject;

public:
    GameLevel();
    virtual ~GameLevel();

    void SpawnGameObjects();
    //called by the game loop
    virtual void Update(int64_t deltaTime);
    virtual void Render(sf::RenderWindow* window);

    //Spawn d'un nouveau GameObject et passage des arguments à la fonction Activate
    template <class T = GameObject, typename ...Args>
    T* SpawnActor(Args ...args)
    {
        for (auto* object : m_lObjectsDeactivate)
        {
            auto* tmp = dynamic_cast<T*>(object);
            if (tmp)
            {
                tmp->Activate(args...);
                ActivateObject(*tmp, false);
                return tmp;
            }
        }
        T* newObject = new T();
        newObject->Activate(args...);
        return newObject;
    }

    void AddObjectWithCollision(CollisionHandler& object);
    void RemoveObjectWithCollision(GameObject& object);
    void AddObjectRendered(RenderHandler& object);
    void RemoveObjectRendered(GameObject& object);

    //appelé à la mort du joueur
    virtual void EndGame();

public:

    /// <summary>
    /// Peut etre mettre en place l'intrusive liste pour optimiser un trie par insertion
    /// faire un foreach sur la liste jusqua trouver la bonne place et inserer l'objet au bonne endroit
    /// Insertion plus optimiser avec intrusive liste
    /// </summary>
    Player* m_player = nullptr;

private:
    std::list<GameObject*> m_lObjectsActivate;
    std::list<GameObject*> m_lObjectsRendered;
    std::list<GameObject*> m_lObjectsWithCollision;
    std::list<GameObject*> m_lObjectsDeactivate;

    void ActivateObject(GameObject& object, bool newObject);
    void DeactivateObject(GameObject& object);
};


#endif //GAMELEVEL_H
