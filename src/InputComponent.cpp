#include "InputComponent.h"
#include "Engine.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "BodyComponent.h"
#include <iostream>
#include "BoxComponent.h"
#include "BulletComponent.h"

void InputComponent::spawnBullet() {
    auto bullet = std::make_unique<GameObject>();
    bullet->add<SpriteComponent>("enemy.png");
    bullet->add<BodyComponent>(300, 300, 32, 32, 0, 0, 0);
    bullet->add<BoxComponent>(32, 32);
    Engine::addGameObject(std::move(bullet));
    std::cout << "Bullet spawned" << std::endl;
    
}

void InputComponent::destroyBullet() {
    GameObject* bullet = &this->parent();
    Engine::removeGameObject(bullet);
    std::cout << "Bullet destroyed" << std::endl;
}