#pragma once

#include "Component.h"
#include "BodyComponent.h"
#include "Engine.h"
#include <box2d/box2d.h>
#include <iostream>
#include "GameObject.h"

class StaticComponent : public Component {
public:
    StaticComponent(GameObject& owner, double width, double height) : Component(owner), width(width), height(height) {
        createBody(width, height);
    }

    void update() override {
        auto body = parent().get<BodyComponent>();

        if (body) {
            body->x() = static_cast<float>(body->x());
            body->y() = static_cast<float>(body->y());
        }

        //std::cout << "Box Location: " << body->x() << ", " << body->y() << std::endl;
    }

    void draw() override {}

private:
    void createBody(float widthPixels, float heightPixels) {
        auto bodyComp = parent().get<BodyComponent>();
        if (!bodyComp) return;

        const float PIXELS_PER_METER = 32.0f;
        b2WorldId worldId = Engine::getWorldId();

        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = {pixelsToMeters(static_cast<float>(bodyComp->x())), pixelsToMeters(static_cast<float>(bodyComp->y()))};
        bodyDef.fixedRotation = true; 
        b2BodyId boxBodyId = b2CreateBody(worldId, &bodyDef);

        b2Polygon box;
        box = b2MakeBox(pixelsToMeters(widthPixels) / 2.0f, pixelsToMeters(heightPixels) / 2.0f);
        b2ShapeDef shapeDef = b2DefaultShapeDef();
        shapeDef.density = 1.0f;
        b2ShapeId boxShapeId = b2CreatePolygonShape(boxBodyId, &shapeDef, &box);
        b2Shape_SetRestitution(boxShapeId, .8f);
    }

    float width;
    float height;

    float pixelsToMeters(float pixels) const { return pixels / 32.0f; }
    float metersToPixels(float meters) const { return meters * 32.0f; }
};