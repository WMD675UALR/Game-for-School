#pragma once
#include "Component.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "GameObject.h"
#include "BodyComponent.h"
#include "Input.h"
#include "BulletComponent.h"
#include "SpriteComponent.h"
#include "FPS.h"
#include "StatComponent.h"
#include "BoxComponent.h"
#include <box2d/box2d.h>
#include "AudioComponent.h"

class Engine;

class InputComponent : public Component {
public:
    InputComponent(GameObject& parent) : Component(parent) {}
    void update() override {
        float deltaTime = fps.getDeltaTime();
        fps.update();

        auto body = this->parent().get<BodyComponent>();
        auto box = this->parent().get<BoxComponent>();
        auto stat = this->parent().get<StatComponent>();
        if (!body || !box) return;
        
        // Accumulate velocity from all pressed keys
        float velX = 0.0f;
        float velY = 0.0f;
        
        if(Input::isKeyDown(SDLK_w)) {
            body->y() -= 100 * deltaTime;
            velY -= 10.0f * (deltaTime * stat->getSpeed());
        }
        if(Input::isKeyDown(SDLK_s)) {
            body->y() += 100 * deltaTime;
            velY += 10.0f * (deltaTime * stat->getSpeed());
        }
        if(Input::isKeyDown(SDLK_a)) {
            body->x() -= 100 * deltaTime;
            velX -= 10.0f * (deltaTime * stat->getSpeed());

            //Swap png when going left
        }
        if(Input::isKeyDown(SDLK_d)) {
            body->x() += 100 * deltaTime;
            velX += 10.0f * (deltaTime * stat->getSpeed());
            //swap png when going right
        }
        // Apply combined velocity (allows diagonal movement)
        box->ApplyLinearVelocity({velX, velY});
        if(Input::isMouseButtonDown(SDL_BUTTON_LEFT)) {
            auto mousePosition = Input::getMousePosition();
            std::cout << "Mouse position: " << mousePosition.first << ", " << mousePosition.second << std::endl;
        
            if(timer > 10) {
                std::cout << "Shooting" << std::endl;
                spawnBullet(mousePosition);
                
                // Play sound when shooting
                auto audio = this->parent().get<AudioComponent>();
                if(audio) {
                    audio->playSound();
                }
                
                timer = 0;
            }
        }

        if(Input::isMouseButtonDown(SDL_BUTTON_RIGHT)) {
        }
        timer++;

    }
    void draw() override {}

    void spawnBullet(const std::pair<int, int>& mousePosition);
    void destroyBullet();
    
private:
    FPS fps;
    int timer = 0;
    int velocity = 100;
};