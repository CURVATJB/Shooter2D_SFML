#include "Components/ShootComponents/ShootBulletComponent.h"
#include "GameObjects/Bullets/GenericBullet.h"
#include "GameWindow.h"


ShootBulletComponent::ShootBulletComponent()
{
    m_fireRate = 1;
    m_shootNumber = 1;
}

void ShootBulletComponent::ShootBullet(int initialAngle)
{    
    // Print::PrintLog("shoot");
    GenericBullet* bullet = GameWindow::GetGameLevel()->SpawnActor<GenericBullet>();
    bullet->position = Owner->position;
    bullet->rotation = Owner->rotation + initialAngle;
}

