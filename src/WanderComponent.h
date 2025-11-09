#pragma once
#include "Component.h"
#include "BodyComponent.h"
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
            wandering();
            timer = 0.0f;
        }

    }

    void wandering() {

        auto body = parent().get<BodyComponent>();

        if (!body) return;

        body->vx() = random(-5, 5);
        body->vy() = random(-5, 5);
        body->x() += body->vx();
        body->y() += body->vy();
    }


private:
    double speed;
    double timer;
};