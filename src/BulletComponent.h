#pragma once
#include "Component.h"
#include "GameObject.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "ChasingComponent.h"
#include "TrackingComponent.h"
#include "DecayComponent.h"
#include "Engine.h"
#include <iostream>
#include <chrono>

class BulletComponent : public Component {
public:
    BulletComponent(GameObject& parent, GameObject& target) : Component(parent), target(&target) {}

    void update() override {}

    void draw() override {
        auto body = parent().get<BodyComponent>();

        if (!body) return;

        auto targetBody = target->get<BodyComponent>();

        if (!targetBody) return;
        
        body->angle() = atan2(targetBody->y() - body->y(), targetBody->x() - body->x());
        body->vx() = cos(body->angle()) * 10;
        body->vy() = sin(body->angle()) * 10;
        
        body->x() += body->vx();
        body->y() += body->vy();

        if(hypot(targetBody->x() - body->x(), targetBody->y() - body->y()) < 5) {
            std::cout << "Collision detected" << std::endl;
        }
    }
private:
    GameObject* target;
    int leftx;
    int rightx;

};