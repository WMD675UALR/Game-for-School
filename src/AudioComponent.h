#pragma once

#include "Component.h"
#include "GameObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Engine.h"
#include <memory>
#include <iostream>


class AudioComponent : public Component {
public:
    AudioComponent(GameObject& parent, std::string soundKey) : Component(parent), sound(nullptr) {
        sound = Mix_LoadWAV(soundKey.c_str());
        if (!sound) {
            SDL_Log("Failed to load sound for key: %s - Error: %s", soundKey.c_str(), Mix_GetError());
        } else {
            SDL_Log("Successfully loaded sound: %s", soundKey.c_str());
        }
    }

    void update() override {}

    void draw() override {}

    void playSound() {
        if (!sound) {
            return;
        }
        
        int channel = Mix_PlayChannel(-1, sound, 0);
        if (channel == -1) {
            SDL_Log("Failed to play sound: %s", Mix_GetError());
        } else {
            Mix_VolumeChunk(sound, MIX_MAX_VOLUME);
        }
    }

private:
    Mix_Chunk* sound;
};
