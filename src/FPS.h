#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class FPS {
public:
    void update() {
        int currentTime = SDL_GetTicks();
        frameTime = currentTime - lastTime;
        lastTime = currentTime;


        if (targetFrameTime > frameTime) {
            SDL_Delay(targetFrameTime - frameTime);
            frameTime = targetFrameTime;
        } 

        float currentFPS = 1000.0f / frameTime;
        //std::cout << "FPS: " << currentFPS << std::endl;
        deltaTime = 2 * (frameTime / 1000.0f);

        //std::cout << "deltaTime" << getDeltaTime() << std::endl;
    }

    float getDeltaTime() {
        return deltaTime;
    }

    int getWorldExp() {
        return worldExp;
    }

    void setWorldExp(int exp) {
        worldExp = exp;
    }

private:
    int targetFrameTime = 1000/60;
    int idealFPS = 60;
    Uint32 lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;
    int frameTime = 0;
    int worldExp = 0;
};