cmake_minimum_required(VERSION 3.2)

project(Shooter2D_SFML VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


set(HEADERS
	${HEADER_DIR}/StaticData.h
	${HEADER_DIR}/Signal.h
    ${HEADER_DIR}/Singleton.h
	${HEADER_DIR}/GameLevel.h
    ${HEADER_DIR}/GameLoop.h
    ${HEADER_DIR}/GameWindow.h
    ${HEADER_DIR}/Tools/Print.h
    ${HEADER_DIR}/Tools/VectorTools.h
    ${HEADER_DIR}/Tools/SMath.h    
    ${HEADER_DIR}/GameObjects/Player.h
    ${HEADER_DIR}/GameObjects/Bullet.h
    ${HEADER_DIR}/GameObjects/GameObject.h
    ${HEADER_DIR}/GameObjects/Character.h
    ${HEADER_DIR}/GameObjects/IBonus.h
    ${HEADER_DIR}/GameObjects/BonusHeal.h
    ${HEADER_DIR}/GameObjects/BonusFireRate.h
    ${HEADER_DIR}/GameObjects/BonusShotgun.h
    ${HEADER_DIR}/GameObjects/BonusSniper.h
    ${HEADER_DIR}/GameObjects/BonusMovementSpeed.h
    ${HEADER_DIR}/GameObjects/BonusMultipleShot.h
	${HEADER_DIR}/GameObjects/EnemySpawner.h
	${HEADER_DIR}/GameObjects/Enemy.h    
    ${HEADER_DIR}/Managers/TextureManager.h
    ${HEADER_DIR}/Managers/AudioManager.h
    ${HEADER_DIR}/Managers/ScoreManager.h
    ${HEADER_DIR}/Managers/FontManager.h
    ${HEADER_DIR}/Managers/CollisionManager.h
    ${HEADER_DIR}/Managers/InputManager.h
    ${HEADER_DIR}/Managers/CollisionDispatcher.h
    ${HEADER_DIR}/Managers/TOnCollision.h
    ${HEADER_DIR}/Components/Component.h
    ${HEADER_DIR}/Components/RenderHandler.h
    ${HEADER_DIR}/Components/ShootComponent.h
    ${HEADER_DIR}/Components/CollisionHandler.h
    ${HEADER_DIR}/Components/PlayerMovementComponent.h
    ${HEADER_DIR}/Components/LifeComponent.h
    ${HEADER_DIR}/Components/Sniper.h
    ${HEADER_DIR}/Components/ShotGun.h
    ${HEADER_DIR}/Components/ClassicPistol.h
	${HEADER_DIR}/Components/KamikazeMovementComponent.h
	${HEADER_DIR}/Components/IMovementComponent.h
	${HEADER_DIR}/Components/RunAwayMovementComponent.h
	${HEADER_DIR}/Components/BaseEnemyMovementComponent.h
    ${HEADER_DIR}/HUD/PlayerHUD.h      	
    ${HEADER_DIR}/HUD/EndScreenHUD.h
	
)

set(SOURCES
    ${SOURCE_DIR}/Main.cpp
    ${SOURCE_DIR}/GameLoop.cpp
    ${SOURCE_DIR}/GameLevel.cpp
    ${SOURCE_DIR}/GameWindow.cpp
    ${SOURCE_DIR}/GameObjects/GameObject.cpp
    ${SOURCE_DIR}/GameObjects/Player.cpp
    ${SOURCE_DIR}/GameObjects/Bullet.cpp
    ${SOURCE_DIR}/GameObjects/Character.cpp
	${SOURCE_DIR}/GameObjects/EnemySpawner.cpp
	${SOURCE_DIR}/GameObjects/Enemy.cpp
    ${SOURCE_DIR}/Managers/TextureManager.cpp
    ${SOURCE_DIR}/Managers/AudioManager.cpp
    ${SOURCE_DIR}/Managers/ScoreManager.cpp
    ${SOURCE_DIR}/Managers/FontManager.cpp
    ${SOURCE_DIR}/Managers/CollisionManager.cpp
    ${SOURCE_DIR}/Managers/InputManager.cpp
    ${SOURCE_DIR}/Components/CollisionHandler.cpp
    ${SOURCE_DIR}/Components/RenderHandler.cpp
    ${SOURCE_DIR}/Components/ShootComponent.cpp
    ${SOURCE_DIR}/Components/PlayerMovementComponent.cpp
    ${SOURCE_DIR}/Components/Sniper.cpp
    ${SOURCE_DIR}/Components/ShotGun.cpp
    ${SOURCE_DIR}/Components/ClassicPistol.cpp
    ${SOURCE_DIR}/Components/LifeComponent.cpp
	${SOURCE_DIR}/Components/KamikazeMovementComponent.cpp
	${SOURCE_DIR}/Components/RunAwayMovementComponent.cpp
	${SOURCE_DIR}/Components/BaseEnemyMovementComponent.cpp
    ${SOURCE_DIR}/HUD/PlayerHUD.cpp
	${SOURCE_DIR}/HUD/EndScreenHUD.cpp
	
	
)


source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
PREFIX "SOURCES"
FILES ${SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
PREFIX "HEADERS"
FILES ${HEADERS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${HEADER_DIR}   
)