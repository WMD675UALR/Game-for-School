#pragma once
#include "Component.h"
#include "GameObject.h"
#include <iostream>
#include "FPS.h"

class StatComponent : public Component {
public:
    StatComponent(GameObject& parent, int health, int maxHealth, int speed, int attack, int defense, int luck, int experience, int level, int expDrop) : 
    Component(parent), health(health), maxHealth(maxHealth), speed(speed), attack(attack), defense(defense), luck(luck), experience(experience), level(level), expDrop(expDrop) {}
    void update() override {
        if (fps.getWorldExp() >= level * 10) {
            level++;
            experience = 0;
            maxHealth += 10;
            health = maxHealth;
            attack += 1;
            defense += 1;
            luck += 1;
        }
    }
    void draw() override {}

    int getHealth() { return health; }
    int getMaxHealth() { return maxHealth; }
    int getSpeed() { return speed; }
    int getAttack() { return attack; }
    int getDefense() { return defense; }
    int getLuck() { return luck; }
    int getExperience() { return experience; }
    int getLevel() { return level; }
    int getExpDrop() { return expDrop; }
    void setHealth(int health) { this->health = health; }
    void setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; }
    void setSpeed(int speed) { this->speed = speed; }
    void setAttack(int attack) { this->attack = attack; }
    void setDefense(int defense) { this->defense = defense; }
    void setLuck(int luck) { this->luck = luck; }
    void setExperience(int experience) { this->experience = experience; }
    void setLevel(int level) { this->level = level; }
    void setExpDrop(int expDrop) { this->expDrop = expDrop; }
private:
    int health;
    int maxHealth;
    int speed;
    int attack;
    int defense;
    int luck;
    int experience;
    int level;
    int expDrop;
    FPS fps;
};