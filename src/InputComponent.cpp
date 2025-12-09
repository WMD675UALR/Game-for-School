#include "InputComponent.h"
#include "Engine.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "BodyComponent.h"
#include <iostream>
#include <cmath>
#include "BoxComponent.h"
#include "BulletComponent.h"
#include "StatComponent.h"

void InputComponent::spawnBullet(const std::pair<int, int>& mousePosition) {
    auto body = this->parent().get<BodyComponent>();
    if (!body) return;

    float playerX = body->x();
    float playerY = body->y();
    float playerWidth = body->width();
    float playerHeight = body->height();

    float mouseX = mousePosition.first;
    float mouseY = mousePosition.second;
    
    float dx = mouseX - playerX;
    float dy = mouseY - playerY;
    float distance = sqrtf(dx * dx + dy * dy);
    

    if (distance > 0.0f) {
        dx /= distance;
        dy /= distance;
    } else {
        dx = 1.0f;
        dy = 0.0f;
    }
    
    float bulletWidth = 32.0f;
    float bulletHeight = 32.0f;
    float playerRadius = sqrtf((playerWidth * playerWidth + playerHeight * playerHeight)) / 2.0f;
    float bulletRadius = sqrtf((bulletWidth * bulletWidth + bulletHeight * bulletHeight)) / 2.0f;
    float buffer = 5.0f;
    float offset = playerRadius + bulletRadius + buffer;
    
    float bulletX = playerX + dx * offset;
    float bulletY = playerY + dy * offset;

    //float mouseX = mousePosition.first;
    //float mouseY = mousePosition.second;

    //float bodyX = body->x();
    //float bodyY = body->y();

    //float bulletX;
    //float bulletY;

    //if(mouseX < bodyX) {
    //    bulletX = bodyX - 30;
    //} else {
    //    bulletX = bodyX + 30;
    //}
    //if(mouseY < bodyY) {
    //    bulletY = bodyY - 30;
    //} else {
    //    bulletY = bodyY + 0;
    //}

    auto bullet = std::make_unique<GameObject>();
    bullet->add<SpriteComponent>("enemy.png");
    bullet->add<BodyComponent>(bulletX, bulletY, 32, 32, 0, 0, 0);
    bullet->add<BoxComponent>(32, 32);
    bullet->add<BulletComponent>(mousePosition);
    bullet->add<StatComponent>(100, 100, 10, 50, 10, 10, 0, 0, 0);
    Engine::addGameObject(std::move(bullet));
    std::cout << "Bullet spawned" << std::endl;
    
}

void InputComponent::destroyBullet() {
    GameObject* bullet = &this->parent();
    Engine::removeGameObject(bullet);
    std::cout << "Bullet destroyed" << std::endl;
}