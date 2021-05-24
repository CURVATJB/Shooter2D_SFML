#ifndef COLLISIONDISPATCHER_H
#define COLLISIONDISPATCHER_H

#include <functional>
#include <stdexcept>
#include "TOnCollision.h"

using FnType = std::function<void(GameObject&, GameObject&)>;

template<typename ...types>
struct TypeList
{};

using AllCollisionTypes = TypeList<Player, Enemy, Bullet, BonusHeal, BonusMultipleShot, BonusFireRate, BonusShotgun, BonusSniper, BonusMovementSpeed>;

template<template<typename, typename> class Functor, typename T1, typename T2TypeList>
struct DispatchOnT2
{};

template<template<typename, typename> class Functor, typename T1>
struct DispatchOnT2<Functor, T1, TypeList<> >
{
	static FnType CheckType(TypeId t2) { throw std::runtime_error("Type not in typelist of Collision"); }
};

template<template<typename, typename> class Functor, typename T1, typename FirstT2Type, typename ...OtherT2Types>
struct DispatchOnT2<Functor, T1, TypeList<FirstT2Type, OtherT2Types...> >
{
	static FnType CheckType(TypeId t2)
	{
		if (t2 == FirstT2Type::GetClassTypeId())
		{
			return [](GameObject& go1, GameObject& go2)
			{
				if (!Functor<T1, FirstT2Type>::Reaction(static_cast<T1&>(go1), static_cast<FirstT2Type&>(go2)))
				{
					Functor<FirstT2Type, T1>::Reaction(static_cast<FirstT2Type&>(go2), static_cast<T1&>(go1));
				}
			};
		}
		return DispatchOnT2<Functor, T1, TypeList<OtherT2Types...> >::CheckType(t2);
	}
};

template<template<typename, typename> class Functor, typename AllAdmissibleTypes, typename T1TypeList>
struct DispatchOnT1
{};

template<template<typename, typename> class Functor, typename AllAdissibleTypes>
struct DispatchOnT1<Functor, AllAdissibleTypes, TypeList<> >
{
	static FnType CheckType(TypeId t1, TypeId t2) { throw std::runtime_error("Type not in typelist of Collision"); }
};

template<template<typename, typename> class Functor, typename AllAdmissibleTypes, typename FirstT1Type, typename ...OtherT1Types>
struct DispatchOnT1<Functor, AllAdmissibleTypes, TypeList<FirstT1Type, OtherT1Types...> >
{
	static FnType CheckType(TypeId t1, TypeId t2)
	{
		if (t1 == FirstT1Type::GetClassTypeId())
		{
			return DispatchOnT2<Functor, FirstT1Type, AllAdmissibleTypes>::CheckType(t2);
		}
		return DispatchOnT1<Functor, AllAdmissibleTypes, TypeList<OtherT1Types...> >::CheckType(t1, t2);
	}
};

/// <summary>
/// Class utilisée pour trouver les types des objets qui collisionnent et appelée la bonne surcharge de classe TOnCollision
/// </summary>
class CollisionDispatcher
{
public:
	static void DispatchOnCollision(GameObject& go1, GameObject& go2)
	{
		DispatchOnT1<OnCollision, AllCollisionTypes, AllCollisionTypes>::CheckType(go1.GetTypeId(), go2.GetTypeId())(go1, go2);
	}
};
#endif //COLLISIONDISPATCHER_H