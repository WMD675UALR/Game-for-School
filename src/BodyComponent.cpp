#include "BodyComponent.h"

BodyComponent::BodyComponent(GameObject& owner, float x, float y, int width, int height, float angle, float vx, float vy) 
    : Component(owner), _x(x), _y(y), _width(width), _height(height), _angle(angle), _vx(vx), _vy(vy) {}


void BodyComponent::update() {
    _x += _vx;
    _y += _vy;

    //_x += _vx * _deltaTime;
    //_y += _vy * _deltaTime;
}