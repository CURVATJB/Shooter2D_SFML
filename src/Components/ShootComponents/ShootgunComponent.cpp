#include "Components/ShootComponents/ShootgunComponent.h"
#include "GameObjects/Bullets/GenericBullet.h"
#include "GameWindow.h"

ShootgunComponent::ShootgunComponent()
{
    m_fireRate = 3;
    m_shootNumber = 7;
    m_dispersion = 3;
}

void ShootgunComponent::ShootBullet(int initialAngle)
{
    // Print::PrintLog("shoot");
    GenericBullet* bullet = GameWindow::GetGameLevel()->SpawnActor<GenericBullet>();
    bullet->position = Owner->position;
    bullet->rotation = Owner->rotation + initialAngle;
    bullet->autoDestroyDelay = 0.2f;
    bullet->speedMultiply = 2.f;
}

