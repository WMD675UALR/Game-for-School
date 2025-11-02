#pragma once
#include "Component.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "GameObject.h"
#include "BodyComponent.h"
#include "Input.h"
#include "Engine.h"


class InputComponent : public Component {
public:
    InputComponent(GameObject& parent) : Component(parent) {}
    void update() override {
        if(Input::isKeyDown(SDLK_w)) {
            auto body = this->parent().get<BodyComponent>();
            body->y() -= 10;
            //std::cout << "Moving up" << std::endl;
        }
        if(Input::isKeyDown(SDLK_a)) {
            auto body = this->parent().get<BodyComponent>();
            body->x() -= 10;
            //std::cout << "Moving left" << std::endl;

            //Swap png when going left
        }
        if(Input::isKeyDown(SDLK_s)) {
            auto body = this->parent().get<BodyComponent>();
            body->y() += 10;
            //std::cout << "Moving down" << std::endl;
        }
        if(Input::isKeyDown(SDLK_d)) {
            auto body = this->parent().get<BodyComponent>();
            body->x() += 10;
            //std::cout << "Moving right" << std::endl;

            //swap png when going right
        }
        if(Input::isMouseButtonDown(SDL_BUTTON_LEFT)) {
            

            std::cout << "Shooting" << std::endl;
            
        }
    }
    void draw() override {}

private:
};