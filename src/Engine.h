#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>  // For std::unique_ptr
#include <algorithm>  // For std::remove_if
#include "GameObject.h"
#include "Input.h"
#include "BodyComponent.h"
#include <iostream>
#include "FPS.h"
#include <box2d/box2d.h>
#include <SDL2/SDL_mixer.h>
#include <string>

struct ViewportOffset {
    float x{0.0f};
    float y{0.0f};
};

class Engine {
public:
    static int width;
    static int height;

    // Initialize the Engine (static)
    static bool init(const char* title, int width, int height) {
        Engine::width = width;
        Engine::height = height;

        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity = {0.0f, 0.0f};
        worldId = b2CreateWorld(&worldDef);


        SDL_Init(SDL_INIT_AUDIO);
        Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC);
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            SDL_Log("Failed to open audio: %s", Mix_GetError());
        } else {
            SDL_Log("Audio initialized successfully");
        }
        Mix_Volume(-1, MIX_MAX_VOLUME); // Set max volume for all channels
    
        Mix_Chunk* backgroundMusic = Mix_LoadWAV("assets/music/Background.wav");
        if (!backgroundMusic) {
            SDL_Log("Failed to load background music: %s", Mix_GetError());
            return false;
        }
        Mix_PlayChannel(-1, backgroundMusic, -1);


        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
            return false;
        }

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        if (!window) {
            SDL_Log("Failed to create window: %s", SDL_GetError());
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            SDL_Log("Failed to create renderer: %s", SDL_GetError());
            return false;
        }

        isRunning = true;
        return true;
    }

    // Handle events (static)
    static void handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            Input::processEvent(event);  // Call static Input method
        }
    }

    // Update all game objects (static)

    static void update() {
        for (auto& gameObject : gameObjects) {
            gameObject->update();  // Update each GameObject
        }

        for (auto& newObj : pendingObjects) {
            gameObjects.push_back(std::move(newObj));
        }
        
        // Remove destroyed objects
        gameObjects.erase(
            std::remove_if(gameObjects.begin(), gameObjects.end(),
                [](const std::unique_ptr<GameObject>& obj) {
                    return obj->isBeingDestroyed();
                }),
            gameObjects.end()
        );


        const float timeStep = 1.0f / 60.0f;
        const int subStepCount = 4;

        b2World_Step(worldId, timeStep, subStepCount);
        //std::cout << "Physics updated" << std::endl;

        pendingObjects.clear();

        if (cameraTarget) {
            if (auto body = cameraTarget->get<BodyComponent>()) {
                const float targetX = static_cast<float>(width) * 0.5f - static_cast<float>(body->width()) * 0.5f - static_cast<float>(body->x());
                const float targetY = static_cast<float>(height) * 0.5f - static_cast<float>(body->height()) * 0.5f - static_cast<float>(body->y());

                viewport.x = targetX;
                viewport.y = targetY;
            }
        }
    }

    // Render all game objects (static)
    static void render() {
        SDL_SetRenderDrawColor(renderer, 94, 92, 87, 255);
        SDL_RenderClear(renderer);

        for (auto& gameObject : gameObjects) {
            gameObject->draw();  // Draw each GameObject
        }

        SDL_RenderPresent(renderer);
    }

    // Clean up SDL resources (static)
    static void clean() {
        b2DestroyWorld(worldId);
        worldId = b2_nullWorldId;

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
        SDL_Quit();
    }

    // Check if the engine is still running (static)
    static bool running() {
        return isRunning;
    }

    // Add a GameObject to the engine (static)
    static void addGameObject(std::unique_ptr<GameObject> gameObject) {
        //gameObjects.push_back(std::move(gameObject));  // Add the game object to the list
        pendingObjects.push_back(std::move(gameObject));  // Add the game object to the pending list
    }

    static void removeGameObject(GameObject* gameObject) {
        // Find and mark the object for removal
        if (gameObject) {
            gameObject->destroy();
        }
    }

    static b2WorldId getWorldId() {
        return worldId;
    }
    //Run the engine (static)
    
    static void run() {
        while (isRunning) {
            handleEvents();
            update();
            render();
            fps.update();

        }

    }

    static SDL_Renderer* getRenderer() {
        return renderer;
    }

    static void setCameraTarget(GameObject* target) {
        cameraTarget = target;
    }

    static const ViewportOffset& getViewport() {
        return viewport;
    }

    // Get all game objects (for collision detection)
    static const std::vector<std::unique_ptr<GameObject>>& getGameObjects() {
        return gameObjects;
    }

    //int addObject();
    //Object* getObject(int uuid) {return objects[uuid].get();}

private:
    static bool isRunning;                               // Engine running state (static)
    static SDL_Window* window;                           // SDL window (static)
    static SDL_Renderer* renderer;                       // SDL renderer (static)
    static std::vector<std::unique_ptr<GameObject>> gameObjects;  // Track game objects
    static std::vector<std::unique_ptr<GameObject>> pendingObjects;  // Objects to add next frame
    static std::vector<std::unique_ptr<GameObject>> dyingObjects;  // Objects to remove next frame
    static ViewportOffset viewport;
    static GameObject* cameraTarget;
    static FPS fps;
    static b2WorldId worldId;
    //static std::map<int, std::unique_ptr<Object>> objects;
    //int uuidCounter = 0;
    //static std::map<int, std::unique_ptr<GameObject>> objectsToAdd;
};
