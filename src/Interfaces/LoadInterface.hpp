#pragma once

class LoadInterface {
public:
    virtual void Load() = 0;
    virtual ~LoadInterface() = default;
};
