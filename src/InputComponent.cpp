#include "InputComponent.h"
#include "Engine.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "BodyComponent.h"
#include <iostream>

void InputComponent::spawnBullet() {
    auto bullet = std::make_unique<GameObject>();
    bullet->add<SpriteComponent>("enemy");
    bullet->add<BodyComponent>(300, 300, 10, 10, 0, 0, 0);
    Engine::addGameObject(std::move(bullet));
    std::cout << "Bullet spawned" << std::endl;
}