#pragma once
#include "Component.h"
#include "BodyComponent.h"
#include "TrackingComponent.h"
#include <cmath>
#include <iostream>
#include "AudioComponent.h"
#include "Engine.h"
#include "FPS.h"


class ChasingComponent : public Component {
public:
    ChasingComponent(GameObject& parent, GameObject& target) : Component(parent), target(&target) {
        speed = 3.0f;
    }
    
    void update() override {
        float deltaTime = fps.getDeltaTime();
        fps.update();
        if (!target) return;

        auto body = parent().get<BodyComponent>();
        auto targetBody = target->get<BodyComponent>();

        if (!targetBody) return;

        if (hypot(targetBody->x() - body->x(), targetBody->y() - body->y()) < 50 && timer > 2) {
            std::cout << "Collision detected" << std::endl;
            auto audio = parent().get<AudioComponent>();
            if (audio) {
                audio->playSound();
            }
            timer = 0;
        }
        timer += 1 * deltaTime;
    }

    void draw() override {
        auto body = parent().get<BodyComponent>();

        if (!body) return;

        auto targetBody = target->get<BodyComponent>();

        if (!targetBody) return;

        float velX = 0.0f;
        float velY = 0.0f;
        
        body->angle() = atan2(targetBody->y() - body->y(), targetBody->x() - body->x());
        velX = cos(body->angle()) * 10;
        velY = sin(body->angle()) * 10;
        
        velX += body->vx() * (2 * (fps.getDeltaTime()));
        velY += body->vy() * (2 * (fps.getDeltaTime()));

        ApplyLinearVelocity({velX, velY});

        if(hypot(targetBody->x() - body->x(), targetBody->y() - body->y()) < 5) {
            //std::cout << "Collision detected" << std::endl;
        }
    }

    void ApplyLinearVelocity(b2Vec2 velocity) {
        auto bodyComp = parent().get<BodyComponent>();
        if (!bodyComp) return;

        b2Body_SetLinearVelocity(bodyComp->bodyId, velocity);
    }

private:
    double speed;
    int leftx;
    int rightx;
    GameObject* target;
    FPS fps;
    float timer = 0.0f;
};