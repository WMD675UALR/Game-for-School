#pragma once
#include "Engine.h"
#include "Component.h"
#include "BodyComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include "Textures.h"
#include "GameObject.h"

class SpriteComponent : public Component {
public:
    SpriteComponent(GameObject& parent, std::string textureKey )
        : Component(parent), texture(nullptr) {
        texture = Textures::get(textureKey);
        if (!texture) {
            SDL_Log("Failed to load texture for key: %s", textureKey.c_str());
        }
    }

    void update() override {}

    void draw() override {
        auto body = parent().get<BodyComponent>();
        if (body) {
            const auto& viewport = Engine::getViewport();
            SDL_Rect dst = {
                static_cast<int>(body->x() + viewport.x), static_cast<int>(body->y() + viewport.y), static_cast<int>(body->width()), static_cast<int>(body->height())
            };
            SDL_RenderCopy(Engine::getRenderer(), texture, nullptr, &dst);
        }
    }

private:
    SDL_Texture* texture;
};