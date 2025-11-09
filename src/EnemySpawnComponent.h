#pragma once
#include "Component.h"
#include "GameObject.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "ChasingComponent.h"
#include "TrackingComponent.h"
#include "DecayComponent.h"
#include "Engine.h"
#include <iostream>
#include <chrono>

class EnemySpawnComponent : public Component {
public:
    EnemySpawnComponent(GameObject& object, GameObject& spawnPoint, GameObject& target) : Component(object), _object(object), _spawnPoint(spawnPoint), _target(target), _spawnRate(5.0f), _spawnTimer(0.0f) {}

    void update() override {
        float deltaTime = 1.0f / 60.0f;
        _spawnTimer += deltaTime;
        
        if (_spawnTimer >= _spawnRate) {
            spawnEnemy();
            std::cout << "Spawning enemy" << std::endl;
            //_spawnTimer = -100000;
            _spawnTimer = 0;
        }

    }

    void draw() override {}

    void spawnEnemy() {
        auto enemy = std::make_unique<GameObject>();
        enemy->add<SpriteComponent>("enemy");
        //enemy->add<BodyComponent>(400, 400, 0, 10, 10);
        enemy->add<BodyComponent>(_spawnPoint.get<BodyComponent>()->x(), _spawnPoint.get<BodyComponent>()->y(), 64, 64, 0, 10, 10);
        enemy->add<ChasingComponent>(_target);
        enemy->add<TrackingComponent>(_target);
        Engine::addGameObject(std::move(enemy));
    }

private:
    GameObject& _object;
    GameObject& _target;
    GameObject& _spawnPoint;
    float _spawnRate = 300.0f;
    float _spawnTimer = 0.0f;
};