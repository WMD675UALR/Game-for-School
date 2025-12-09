#pragma once
#include "Component.h"
#include "GameObject.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "ChasingComponent.h"
#include "TrackingComponent.h"
#include "DecayComponent.h"
#include "BoxComponent.h"
#include "StatComponent.h"
#include "FPS.h"
#include "Engine.h"
#include <box2d/box2d.h>
#include <iostream>
#include <chrono>
#include <cmath>

class BulletComponent : public Component {
public:
    BulletComponent(GameObject& parent, std::pair<int, int> mousePosition) : Component(parent) {
        auto body = parent.get<BodyComponent>();
        if (!body) {
            velX = 0.0f;
            velY = 0.0f;
            return;
        }

        float vx = mousePosition.first - body->x();
        float vy = mousePosition.second - body->y();
        float length = sqrtf(vx * vx + vy * vy);
        float bulletSpeed = 15.0f;
        
        if (length > 0.0f) {
            vx /= length;
            vy /= length;
        }
        velX = vx * bulletSpeed;
        velY = vy * bulletSpeed;
        
        body->angle() = atan2(-1 * vx, -1 * vy);

        std::cout << "Bullet angle: " << body->angle() << std::endl;
    }

    void update() override {
        auto body = parent().get<BodyComponent>();
        auto box = parent().get<BoxComponent>();

        if (!body) return;
        if (!box) return;

        box->ApplyLinearVelocity({velX, velY});

        // Check for collisions with enemies
        checkEnemyCollisions();

        if (timer > 3) {
            if (!body) {
                return;
            }
            parent().destroy();
        }
        timer += 1 * deltaTime;

    }

    void draw() override {}

private:
    void checkEnemyCollisions() {
        auto bulletBody = parent().get<BodyComponent>();
        if (!bulletBody) return;

        // Get bullet position and size
        float bulletX = bulletBody->x();
        float bulletY = bulletBody->y();
        float bulletW = bulletBody->width();
        float bulletH = bulletBody->height();
        
        // Bullet's bounding box
        float bulletLeft = bulletX;
        float bulletRight = bulletX + bulletW;
        float bulletTop = bulletY;
        float bulletBottom = bulletY + bulletH;

        const auto& gameObjects = Engine::getGameObjects();
        
        for (const auto& gameObject : gameObjects) {
            if (gameObject.get() == &parent()) continue;
            
            auto chasingComponent = gameObject->get<ChasingComponent>();
            if (!chasingComponent) continue;
            
            auto enemyBody = gameObject->get<BodyComponent>();
            if (!enemyBody) continue;
            
            float enemyX = enemyBody->x();
            float enemyY = enemyBody->y();
            float enemyW = enemyBody->width();
            float enemyH = enemyBody->height();
            
            float enemyLeft = enemyX;
            float enemyRight = enemyX + enemyW;
            float enemyTop = enemyY;
            float enemyBottom = enemyY + enemyH;

            auto enemyStats = gameObject->get<StatComponent>();
            auto bulletStats = parent().get<StatComponent>();

            if (!enemyStats || !bulletStats) {
                continue;
            }
            
            int enemyHealth = gameObject->get<StatComponent>()->getHealth();
            int bulletDamage = parent().get<StatComponent>()->getAttack();

            enemyHealth -= bulletDamage;

            if (bulletLeft < enemyRight && bulletRight > enemyLeft &&
                bulletTop < enemyBottom && bulletBottom > enemyTop) {
                std::cout << "Bullet hit enemy!" << std::endl;

            parent().destroy();

            if (enemyHealth > 0) {
                gameObject->get<StatComponent>()->setHealth(enemyHealth);
            }
                if (enemyHealth <= 0) {
                    gameObject->destroy();
                    fps.setWorldExp(fps.getWorldExp() + bulletStats->getExpDrop());
                    return;
                }
            }   
        }
    }

    FPS fps;
    float velX;
    float velY;
    float timer = 0.0f;
    float deltaTime = 1.0f / 60.0f;
};