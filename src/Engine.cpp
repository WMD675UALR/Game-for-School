#include "Engine.h"

// Definition of static members
bool Engine::isRunning = false;
SDL_Window* Engine::window = nullptr;
SDL_Renderer* Engine::renderer = nullptr;
std::vector<std::unique_ptr<GameObject>> Engine::gameObjects;
std::vector<std::unique_ptr<GameObject>> Engine::pendingObjects;
std::vector<std::unique_ptr<GameObject>> Engine::dyingObjects;
int Engine::width = 0;
int Engine::height = 0;
ViewportOffset Engine::viewport{};
GameObject* Engine::cameraTarget = nullptr;
FPS Engine::fps{};
b2WorldId Engine::worldId{};