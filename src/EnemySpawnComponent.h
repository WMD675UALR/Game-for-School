#pragma once
#include "Component.h"
#include "GameObject.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "ChasingComponent.h"
#include "TrackingComponent.h"
#include "Engine.h"
#include <iostream>
#include <chrono>

class EnemySpawnComponent : public Component {
public:
    EnemySpawnComponent(GameObject& object, GameObject& gameObject1) : Component(object), _object(object), _gameObject1(gameObject1), _spawnRate(5.0f), _spawnTimer(0.0f) {}

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
        enemy->add<BodyComponent>(400, 400, 0, 10, 10);
        enemy->add<ChasingComponent>(_gameObject1);
        enemy->add<TrackingComponent>(_gameObject1);
        Engine::addGameObject(std::move(enemy));
    }

    //void xCord() {
      //  return (_gameObject1.x() + 100);
    //}

    //void yCord() {
      //  return (_gameObject1.y() + 100);
    //}

private:
    GameObject& _object;
    GameObject& _gameObject1;
    float _spawnRate = 300.0f;
    float _spawnTimer = 0.0f;
};