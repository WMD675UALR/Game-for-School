#pragma once
#include "Component.h"

class BodyComponent : public Component {
public:
    BodyComponent(GameObject& owner, double x, double y, double angle, double vx, double vy) 
    : Component(owner), _x(x), _y(y), _angle(angle), _vx(vx), _vy(vy) {}

    double& x() { return _x; }
    double& y() { return _y; }
    double& angle() { return _angle; }
    double& vx() { return _vx; }
    double& vy() { return _vy; }

    void draw () override {
        this->parent();
    }
    void update () override {}


private:
    double _x, _y;
    double _angle, _vx, _vy;
};
