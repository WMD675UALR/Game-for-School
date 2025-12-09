#include "StatComponent.h"

StatComponent::StatComponent(GameObject& parent, float health, float maxHealth, float speed, float attack, float defense, float luck) : 
Component(parent), health(health), maxHealth(maxHealth), speed(speed), attack(attack), defense(defense), luck(luck) {}

void StatComponent::update() {
}