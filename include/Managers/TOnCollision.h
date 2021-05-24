#ifndef TONCOLLISION_H
#define TONCOLLISION_H

#include "Components/LifeComponent.h"
#include "Components/PlayerMovementComponent.h"
#include "Components/ShotGun.h"
#include "Components/Sniper.h"
#include "GameObjects/BonusFireRate.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/Bullet.h"
#include "GameObjects/Player.h"
#include "GameObjects/BonusHeal.h"
#include "GameObjects/BonusMovementSpeed.h"
#include "GameObjects/BonusMultipleShot.h"
#include "GameObjects/BonusShotgun.h"
#include "GameObjects/BonusSniper.h"
#include "Tools/Print.h"

/// <summary>
/// Cette methode ne gere de base la collision que si on envoie les classes A et B dans le bonne ordre
/// Si ce n'est pas le cas, ça appelle notre struct template non spécialisé et donc on rappelle une struct spécialisé en inversant les types
/// Par exemple si on envoie OnCollision<Enemy, Player> on ne passera pas dans la spécialisation OnCollision<Player, Enemy>
/// </summary>

template <typename GameObject1, typename GameObject2>
struct OnCollision
{
    static bool Reaction(GameObject1& g1, GameObject2& g2)
    {
        return false;
        //OnCollision<GameObject2, GameObject1>::Reaction(g2, g1);
    }
};

template <>
struct OnCollision<Player, Enemy>
{
    static bool Reaction(Player& player, Enemy& enemy)
    {
        player.GetComponentOfClass<LifeComponent>()->CollisionDamage(1);
        enemy.GetComponentOfClass<LifeComponent>()->CollisionDamage(5);
        return true;
    }
};

template <>
struct OnCollision<Player, Bullet>
{
    static bool Reaction(Player& player, Bullet& bullet)
    {
        Print::PrintLog("player collision bullet");
        player.GetComponentOfClass<LifeComponent>()->ModifyHealth(-bullet.GetDammage());
        bullet.Deactivate();

        return true;
    }
};

template <>
struct OnCollision<Bullet, Enemy>
{
    static bool Reaction(Bullet& bullet, Enemy& enemy)
    {
        std::cout << "Collision Ennemy, Bullet" << std::endl;
        enemy.m_lifeComponent->ModifyHealth(-(bullet.GetDammage()));
        bullet.Deactivate();

        return true;
    }
};

template <>
struct OnCollision<Player, BonusHeal>
{
    static bool Reaction(Player& player, BonusHeal& bonusHeal)
    {
        auto* life = player.GetComponentOfClass<LifeComponent>();

        life->ModifyHealth(bonusHeal.m_pdtVie);
        Print::PrintLog("take heal ! ");
        bonusHeal.Deactivate();
        return true;
    }
};

template <>
struct OnCollision<Player, BonusMultipleShot>
{
    static bool Reaction(Player& player, BonusMultipleShot& bonusMultipleShot)
    {
        auto* shoot = player.GetComponentOfClass<ShootComponent>();

        shoot->m_additionnalShootNumber++;
        Print::PrintLog("multiple shoot ! : ", shoot->m_additionnalShootNumber);
        bonusMultipleShot.Deactivate();
        return true;
    }
};

template <>
struct OnCollision<Player, BonusFireRate>
{
    static bool Reaction(Player& player, BonusFireRate& bonusFireRate)
    {
        auto shoot = player.GetComponentOfClass<ShootComponent>();

        shoot->m_fireRateModifier *= bonusFireRate.m_fireRateUpAmount;
        Print::PrintLog("fire rate up ! ");
        bonusFireRate.Deactivate();
        return true;
    }
};

template <>
struct OnCollision<Player, BonusShotgun>
{
    static bool Reaction(Player& player, BonusShotgun& bonusShotgun)
    {
        player.SetShootComponent(new ShotGun(*player.GetShootComponent()));

        Print::PrintLog("shotgun ! ");
        bonusShotgun.Deactivate();
        return true;
    }
};

template <>
struct OnCollision<Player, BonusSniper>
{
    static bool Reaction(Player& player, BonusSniper& bonusSniper)
    {
        player.SetShootComponent(new Sniper(*player.GetShootComponent()));

        Print::PrintLog("sniper ! ");
        bonusSniper.Deactivate();
        return true;
    }
};

template <>
struct OnCollision<Player, BonusMovementSpeed>
{
    static bool Reaction(Player& player, BonusMovementSpeed& movementSpeed)
    {
        player.GetComponentOfClass<PlayerMovementComponent>()->m_maxVelocity *= 1.3f;

        Print::PrintLog("movement speed up ! ");
        movementSpeed.Deactivate();
        return true;
    }
};

#endif //TONCOLLISION_H
