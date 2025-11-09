#pragma once
#include <chrono>
#include <iostream>
#include "Engine.h"

class DecayComponent : public Component {
public:
    void update() override {
        float deltaTime = 1.0f / 60.0f;
        _decayTimer += deltaTime;
        if (_decayTimer >= _decayRate) {
            parent().destroy();
        }

    }

private: 
    float _decayRate = 5.0f;
    float _decayTimer = 0.0f;
};