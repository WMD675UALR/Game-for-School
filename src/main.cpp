#define SDL_MAIN_HANDLED
#include "Engine.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "BodyComponent.h"
#include "SlideComponent.h"
#include "TrackingComponent.h"
#include "ChasingComponent.h"
#include "EnemySpawnComponent.h"
#include "BulletComponent.h"
#include "InputComponent.h"
#include "WanderComponent.h"
#include "Input.h"
#include "LevelLoader.h"
#include "Textures.h"
#include "FPS.h"
#include <iostream>
#include <box2d/box2d.h>
#include "BoxComponent.h"
#include "StaticComponent.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Initialize the engine
    if (!Engine::init("SDL2 Game Engine", 800, 600)) {
        return -1;
    }

    SDL_Renderer* renderer = Engine::getRenderer();  // Assuming Engine provides a getRenderer method

    // Load textures into the texture manager
    Textures::load("coin.png", "assets/textures/coin.png", renderer);
    Textures::load("chest.png", "assets/textures/Loot.png", renderer);
    Textures::load("DroneFactory.png", "assets/textures/DroneFactory.png", renderer);
    Textures::load("hero.png", "assets/textures/Playerpngs/Bob.png", renderer);
    Textures::load("enemy.png", "assets/textures/Enemypngs/BasicDronepng1.png", renderer);
    Textures::load("drone.png", "assets/textures/DroneFactory.png", renderer);

    // Load level from XML
    LevelLoader::loadLevel("assets/level1.xml");
    
    auto gameObject1 = std::make_unique<GameObject>();
    gameObject1->add<SpriteComponent>("hero.png");
    gameObject1->add<BodyComponent>(100, 200, 64, 64, 0, 0, 0);
    gameObject1->add<InputComponent>();
    Engine::setCameraTarget(gameObject1.get());
    gameObject1->add<BoxComponent>(64, 64);

    auto gameObject2 = std::make_unique<GameObject>();
    gameObject2->add<SpriteComponent>("coin.png");
    gameObject2->add<BodyComponent>(200, 200, 64, 64, 0, 0, 0);
    gameObject2->add<StaticComponent>(16, 16);

    // Add game objects to the engine
    Engine::addGameObject(std::move(gameObject1));
    Engine::addGameObject(std::move(gameObject2));
    // Run the engine, which will handle updating and drawing the game objects
    Engine::run();

    
    
    return 0;
}