#pragma once
#include "Component.h"
#include "BodyComponent.h"
#include "TrackingComponent.h"
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
    }

    void draw() override {
        auto body = parent().get<BodyComponent>();

        if (!body) return;

        auto targetBody = target->get<BodyComponent>();

        if (!targetBody) return;
        
        body->angle() = atan2(targetBody->y() - body->y(), targetBody->x() - body->x());
        body->vx() = cos(body->angle()) * 10;
        body->vy() = sin(body->angle()) * 10;
        
        body->x() += body->vx() * (2 * (fps.getDeltaTime()));
        body->y() += body->vy() * (2 * (fps.getDeltaTime()));

        if(hypot(targetBody->x() - body->x(), targetBody->y() - body->y()) < 5) {
            //std::cout << "Collision detected" << std::endl;
        }
    }



private:
    double speed;
    int leftx;
    int rightx;
    GameObject* target;
    FPS fps;
};