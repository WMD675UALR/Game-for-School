#define SDL_MAIN_HANDLED
#include "Engine.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "BodyComponent.h"
#include "SlideComponent.h"
#include "TrackingComponent.h"
#include "ChasingComponent.h"
#include "EnemySpawnComponent.h"
#include "InputComponent.h"
#include "Input.h"
#include "LevelLoader.h"
#include "Textures.h"
#include <iostream>

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
    Textures::load("BasicBoss.png", "assets/textures/BasicBoss.png", renderer);
    Textures::load("hero", "assets/textures/Playerpngs/Bob.png", renderer);
    Textures::load("enemy", "assets/textures/Enemypngs/BasicDronepng1.png", renderer);
    //Textures::load("bullet", "assets/textures/squirrel.png", renderer);

    // Load level from XML
    LevelLoader::loadLevel("assets/level1.xml");

    auto gameObject1 = std::make_unique<GameObject>();
    gameObject1->add<SpriteComponent>("hero");  // Use texture key "hero"
    gameObject1->add<BodyComponent>(100, 200, 0, 0, 0);  // BodyComponent with position (100, 200)
    gameObject1->add<EnemySpawnComponent>(*gameObject1);
    gameObject1->add<InputComponent>();
    
    auto gameObject2 = std::make_unique<GameObject>();
    gameObject2->add<SpriteComponent>("enemy");  // Use texture key "enemy"
    gameObject2->add<BodyComponent>(300, 400, 0, 0, 0);  // BodyComponent with position (300, 400)
    //gameObject2->add<ChasingComponent>(*gameObject1);  
    //gameObject2->add<TrackingComponent>(*gameObject1); 
    
    // Add game objects to the engine
    Engine::addGameObject(std::move(gameObject1));
    Engine::addGameObject(std::move(gameObject2));

    // Run the engine, which will handle updating and drawing the game objects
    Engine::run();

    return 0;
}