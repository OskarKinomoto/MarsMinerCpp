#pragma once

class TickInterface {
public:
    virtual void Tick(float dt) = 0;
    virtual ~TickInterface() = default;
};
