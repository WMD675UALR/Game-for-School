#pragma once
#include "Component.h"
#include "BodyComponent.h"
#include "StatComponent.h"
#include "Engine.h"
#include <random>
#include <iostream>

int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

class WanderComponent : public Component {
public:
    WanderComponent(GameObject& parent) : Component(parent) {
        speed = 1.0f;
        timer = 0.0f;
    }
    
    void update() override {}

    void draw() override {

        float deltaTime = 1.0f / 60.0f;
        timer += deltaTime;
        
        if(timer > speed) {
            wandering(deltaTime);
            timer = 0.0f;
        }

    }

    void wandering(float deltaTime) {

        auto body = parent().get<BodyComponent>();
        auto stat = parent().get<StatComponent>();
        if (!body) return;

        float speedMultiplier = stat ? static_cast<float>(stat->getSpeed()) : 30.0f;

        body->vx() = random(-5, 5);
        body->vy() = random(-5, 5);
        body->x() += body->vx() * (deltaTime * speedMultiplier);
        body->y() += body->vy() * (deltaTime * speedMultiplier);

       // std::cout << "Speed Multiplier: " << speedMultiplier << std::endl;
    }


private:
    double speed;
    double timer;
};