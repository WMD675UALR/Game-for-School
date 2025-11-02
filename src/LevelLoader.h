#pragma once
#include <tinyxml2.h>
#include <string>
#include <memory>
#include "GameObject.h"
#include "Engine.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "SlideComponent.h"
#include <SDL2/SDL.h>

class LevelLoader {
public:
    static void loadLevel(const std::string& levelPath) {
        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(levelPath.c_str()) != tinyxml2::XML_SUCCESS) {
            SDL_Log("Failed to load level file: %s", levelPath.c_str());
            return;
        }

        tinyxml2::XMLElement* gameObjectElement = doc.FirstChildElement("GameObject");

        while (gameObjectElement != nullptr) {
            auto gameObject = std::make_unique<GameObject>();
            
            // Parse BodyComponent
            tinyxml2::XMLElement* bodyElement = gameObjectElement->FirstChildElement("BodyComponent");
            if (bodyElement) {
                double x = bodyElement->DoubleAttribute("x", 0.0);
                double y = bodyElement->DoubleAttribute("y", 0.0);
                double angle = bodyElement->DoubleAttribute("angle", 0.0);
                double vx = bodyElement->DoubleAttribute("velocityX", 0.0);
                double vy = bodyElement->DoubleAttribute("velocityY", 0.0);
                
                gameObject->add<BodyComponent>(x, y, angle, vx, vy);
            }
            
            // Parse SpriteComponent
            tinyxml2::XMLElement* spriteElement = gameObjectElement->FirstChildElement("SpriteComponent");
            if (spriteElement) {
                const char* textureKey = spriteElement->Attribute("textureKey");
                if (textureKey) {
                    gameObject->add<SpriteComponent>(std::string(textureKey));
                }
            }
            
            // Parse SlideComponent (if exists)
            tinyxml2::XMLElement* slideElement = gameObjectElement->FirstChildElement("SlideComponent");
            if (slideElement) {
                double speed = slideElement->DoubleAttribute("speed", 5.0);
                int left = slideElement->IntAttribute("left", 0);
                int right = slideElement->IntAttribute("right", 0);
                gameObject->add<SlideComponent>(speed, left, right);
            }
            
            // Add the GameObject to the Engine
            Engine::addGameObject(std::move(gameObject));
            
            // Move to next GameObject
            gameObjectElement = gameObjectElement->NextSiblingElement("GameObject");
        }
        
        SDL_Log("Level loaded successfully: %s", levelPath.c_str());
    }
};

