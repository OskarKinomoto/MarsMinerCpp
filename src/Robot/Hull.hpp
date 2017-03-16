#pragma once

class Hull {
public:
    enum class Model {
        Standard,
        StandardPlus,
    };

public:
    float current = 100;
    Model model = Model::Standard;

public:
    void Hit(float velocityBegin, float velocityEnd);
    void LooseLife(float lifeAmount);

public:
    float Max();
    float Endurance();
    float HitMultiply();

public:
    static float Max(Model m);
    static float Endurance(Model m);
    static float HitMultiply(Model m);
};
