#pragma once

#include "Camera.hpp"

#include "../Utils/Vector2.hpp"
#include "../Utils/Action.hpp"

class CameraGL2 : public CameraBase {
public:
    CameraGL2(Event<SizeI> windowSize);
public:
    void SetPosition(PositionF position, int min, int max) override;
    void Begin() override;
    void Translate() override;
    void TranslateBack() override;

private:
    Event<SizeI> windowSize;
};
