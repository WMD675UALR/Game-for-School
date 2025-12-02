#pragma once
#include "Component.h"
#include <box2d/box2d.h>

class BodyComponent : public Component {
public:
    //BodyComponent(GameObject& owner, double x, double y, double angle, double vx, double vy) 
    //: Component(owner), _x(x), _y(y), _angle(angle), _vx(vx), _vy(vy) {}

    BodyComponent(GameObject& owner, double x, double y, double width, double height, double angle, double vx, double vy) 
    : Component(owner), _x(x), _y(y), _width(width), _height(height), _angle(angle), _vx(vx), _vy(vy) {}
    
    b2BodyId bodyId;

    double& x() { return _x; }
    double& y() { return _y; }
    double& angle() { return _angle; }
    double& vx() { return _vx; }
    double& vy() { return _vy; }
    double& width() { return _width; }
    double& height() { return _height; }

    void draw () override {
        this->parent();
    }
    void update () override {}


private:
    double _x, _y;
    double _angle, _vx, _vy;
    double _width, _height;
};
