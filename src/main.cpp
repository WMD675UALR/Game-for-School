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
#include "StatComponent.h"
#include "LevelLoader.h"
#include "Textures.h"
#include "FPS.h"
#include <iostream>
#include <box2d/box2d.h>
#include "BoxComponent.h"
#include <SDL2/SDL_mixer.h>
#include "StaticComponent.h"
#include "AudioComponent.h"


using namespace std;

int main(int argc, char* argv[]) {
    // Initialize the engine
    if (!Engine::init("SDL2 Game Engine", 800, 600)) {
        return -1;
    }

    SDL_Renderer* renderer = Engine::getRenderer();  // Assuming Engine provides a getRenderer method

    int worldExp = 0;
    // Load textures into the texture manager
    Textures::load("coin.png", "assets/textures/coin.png", renderer);
    Textures::load("chest.png", "assets/textures/Loot.png", renderer);
    Textures::load("DroneFactory.png", "assets/textures/DroneFactory.png", renderer);
    Textures::load("hero.png", "assets/textures/Playerpngs/Bob.png", renderer);
    Textures::load("enemy.png", "assets/textures/Enemypngs/BasicDronepng1.png", renderer);

    // Load level from XML
    LevelLoader::loadLevel("assets/level1.xml");
    
    auto gameObject1 = std::make_unique<GameObject>();
    gameObject1->add<SpriteComponent>("hero.png");
    gameObject1->add<BodyComponent>(100, 200, 64, 64, 0, 0, 0);
    gameObject1->add<InputComponent>();
    Engine::setCameraTarget(gameObject1.get());
    gameObject1->add<BoxComponent>(20, 20);
    gameObject1->add<StatComponent>(100, 100, 30, 50, 10, 10, 0, 1, 0);
    gameObject1->add<AudioComponent>("assets/music/Hit.wav");

    auto gameObject2 = std::make_unique<GameObject>();
    gameObject2->add<SpriteComponent>("enemy.png");
    gameObject2->add<BodyComponent>(500, 500, 64, 64, 0, 0, 0);
    gameObject2->add<BoxComponent>(64, 64);
    gameObject2->add<StatComponent>(100, 100, 20, 10, 10, 10, 0, 1, 10);
    gameObject2->add<ChasingComponent>(*gameObject1);
    gameObject2->add<TrackingComponent>(*gameObject1);
    gameObject2->add<AudioComponent>("assets/music/Hit.wav");

    auto gameObject3 = std::make_unique<GameObject>();
    gameObject3->add<BodyComponent>(-2000, -2000, 64, 64, 0, 0, 0);
    gameObject3->add<BoxComponent>(64, 64);
    gameObject3->add<EnemySpawnComponent>(*gameObject3, *gameObject1);

    auto gameObject4 = std::make_unique<GameObject>();
    gameObject4->add<BodyComponent>(2000, 2000, 64, 64, 0, 0, 0);
    gameObject4->add<BoxComponent>(64, 64);
    gameObject4->add<EnemySpawnComponent>(*gameObject4, *gameObject1);

    auto gameObject5 = std::make_unique<GameObject>();
    gameObject5->add<SpriteComponent>("DroneFactory.png");
    gameObject5->add<BodyComponent>(800, 800, 64, 64, 0, 0, 0);
    gameObject5->add<BoxComponent>(64, 64);
    gameObject5->add<StatComponent>(500, 500, 5, 10, 10, 10, 0, 1, 100);
    gameObject5->add<WanderComponent>();
    gameObject4->add<EnemySpawnComponent>(*gameObject5, *gameObject1);


    Engine::addGameObject(std::move(gameObject1));
    Engine::addGameObject(std::move(gameObject2));
    Engine::addGameObject(std::move(gameObject3));
    Engine::addGameObject(std::move(gameObject4));
    Engine::addGameObject(std::move(gameObject5));
    // Run the engine, which will handle updating and drawing the game objects
    Engine::run();

    
    
    return 0;
}