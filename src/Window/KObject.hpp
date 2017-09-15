#pragma once

#include <set>
#include <memory>

#include "../Interfaces/MouseInterface.hpp"
#include "../Interfaces/PaintInterface.hpp"

#include "../Utils/Vector2.hpp"

class KObject;

typedef std::shared_ptr<KObject> KObjectPtr;

class KObject : public MouseInterface, public PaintInterface  {
public:
    KObjectPtr parent{nullptr};

    std::set<KObjectPtr> childrens;

    Layer layer = Layer::Surface;

    void Add(KObjectPtr obj);

    void Size(SizeUI size);

protected:
    virtual bool OnClose();
    virtual bool OnResize();

    virtual void OnDestroy();
    virtual void OnFocus();

    virtual void AutoSize();

    virtual ~KObject();

private:
    bool visible{false};

    SizeUI size{};
    PositionI position{};
};
