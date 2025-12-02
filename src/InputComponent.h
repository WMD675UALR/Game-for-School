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
#include "BoxComponent.h"
#include <box2d/box2d.h>

class Engine;

class InputComponent : public Component {
public:
    InputComponent(GameObject& parent) : Component(parent) {}
    void update() override {
        float deltaTime = fps.getDeltaTime();
        fps.update();
        if(Input::isKeyDown(SDLK_w)) {
            auto body = this->parent().get<BodyComponent>();
            body->y() -= 100 * deltaTime;
            //std::cout << "Moving up" << std::endl;
            
        }
        if(Input::isKeyDown(SDLK_a)) {
            auto body = this->parent().get<BodyComponent>();
            body->x() -= 100 * deltaTime;
            //std::cout << "Moving left" << std::endl;

            //Swap png when going left
        }
        if(Input::isKeyDown(SDLK_s)) {
            auto body = this->parent().get<BodyComponent>();
            body->y() += 100 * deltaTime;
            //std::cout << "Moving down" << std::endl;
        }
        if(Input::isKeyDown(SDLK_d)) {
            auto body = this->parent().get<BodyComponent>();
            body->x() += 100 * deltaTime;
            //std::cout << "Moving right" << std::endl;

            //swap png when going right
        }
        if(Input::isMouseButtonDown(SDL_BUTTON_LEFT)) {
            

            if(timer > 10) {
                std::cout << "Shooting" << std::endl;
                spawnBullet();
                timer = 0;
            }
        }

        if(Input::isMouseButtonDown(SDL_BUTTON_RIGHT)) {
            
            if(timer > 10) {
                std::cout << "Destroying" << std::endl;
                destroyBullet();
                timer = 0;
            }
        }
        timer++;

    }
    void draw() override {}

    void spawnBullet();
    void destroyBullet();
    
private:
    FPS fps;
    int timer = 0;
    int velocity = 100;

};