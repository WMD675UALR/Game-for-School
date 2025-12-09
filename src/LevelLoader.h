#pragma once
#include <tinyxml2.h>
#include <string>
#include <memory>
#include "GameObject.h"
#include "Engine.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "StatComponent.h"
#include "SlideComponent.h"
#include "StaticComponent.h"
#include "EnemySpawnComponent.h"
#include "TrackingComponent.h"
#include "ChasingComponent.h"
#include "AudioComponent.h"
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
                double width = bodyElement->DoubleAttribute("width", 64.0);
                double height = bodyElement->DoubleAttribute("height", 64.0);
                
                gameObject->add<BodyComponent>(x, y, width, height, angle, vx, vy);
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
            
            tinyxml2::XMLElement* wanderElement = gameObjectElement->FirstChildElement("WanderComponent");
            if (wanderElement) {
                gameObject->add<WanderComponent>();
            }

            tinyxml2::XMLElement* inputElement = gameObjectElement->FirstChildElement("InputComponent");
            if (inputElement) {
                gameObject->add<InputComponent>();
            }

            tinyxml2::XMLElement* statElement = gameObjectElement->FirstChildElement("StatComponent");
            if (statElement) {
                int health = statElement->IntAttribute("health", 100);
                int maxHealth = statElement->IntAttribute("maxHealth", 100);
                int speed = statElement->IntAttribute("speed", 30);
                int attack = statElement->IntAttribute("attack", 10);
                int defense = statElement->IntAttribute("defense", 10);
                int luck = statElement->IntAttribute("luck", 10);
                int experience = statElement->IntAttribute("experience", 0);
                int level = statElement->IntAttribute("level", 1);
                int expDrop = statElement->IntAttribute("expDrop", 10);
                gameObject->add<StatComponent>(health, maxHealth, speed, attack, defense, luck, experience, level, expDrop);
            }

            tinyxml2::XMLElement* audioElement = gameObjectElement->FirstChildElement("AudioComponent");
            if (audioElement) {
                const char* audioKey = audioElement->Attribute("audioKey");
                if (audioKey) {
                    gameObject->add<AudioComponent>(std::string(audioKey));
                }
            }

            // Add the GameObject to the Engine
            Engine::addGameObject(std::move(gameObject));
            
            // Move to next GameObject
            gameObjectElement = gameObjectElement->NextSiblingElement("GameObject");
        }
        
        SDL_Log("Level loaded successfully: %s", levelPath.c_str());
    }
};

