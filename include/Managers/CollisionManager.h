#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <list>

class CollisionHandler;
class GameObject;

class CollisionManager
{
public:
	/// <summary>
	///	Appelée à chaque tick pour actualiser les collisions entre les objets
	/// </summary>
	/// <param name="abscisseTab"> Liste des objets </param>
	static void UpdateCollision(std::list<GameObject*> abscisseTab);

private:
 
	CollisionManager() = default;

	/// <summary>
	///Trie la liste des objets en fonction de la position des objets, de si ils sont activée et si ils possèdent un CollisionHandler
	/// </summary>
	/// <param name="abscisseTab"> Liste des objets </param>
	static void _SortByAbscisse(std::list<GameObject*>& abscisseTab);

	/// <summary>
	/// Check les intersections entres les segments générer à partir de la liste de points du CollisionHandler des objets
	/// </summary>
	/// <param name="g1">Première objet</param>
	/// <param name="g2">Deuxième objet</param>
	static void _CheckCollision(CollisionHandler* g1, CollisionHandler* g2);
};
#endif //COLLISIONMANAGER_H
