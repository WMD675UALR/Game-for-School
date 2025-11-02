#pragma once
#include "Component.h"
#include "BodyComponent.h"
#include <iostream>

class TrackingComponent : public Component {
public:
    TrackingComponent(GameObject& parent, GameObject& targetObj) : Component(parent), target(&targetObj), targetX(0), targetY(0) {}
    void update() override {

        if (!target) return;

        auto body = target->get<BodyComponent>();

        if (!body) return;
        
        targetX = body->x();
        targetY = body->y();
        //std::cout << "Target: " << targetX << ", " << targetY << std::endl;     
        
    }
    void draw() override {}
    
    // Public getters for target position
    float getTargetX() const { return targetX; }
    float getTargetY() const { return targetY; }

private:
    GameObject* target;
    GameObject* object;
    float targetX;
    float targetY;
}; 