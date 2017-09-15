#include "KObject.hpp"

void KObject::Add(KObjectPtr obj)
{
    obj->layer = layer + 0.01f;
    childrens.insert(obj);
}

void KObject::Size(SizeUI size)
{
    auto oldSize = this->size;
    this->size = size;

    if(!OnResize()) {
        this->size = oldSize;
        return;
    }
}

bool KObject::OnClose()
{
    return true;
}

bool KObject::OnResize()
{
    return true;
}

void KObject::OnDestroy()
{

}

void KObject::OnFocus()
{

}

void KObject::AutoSize()
{

}

KObject::~KObject()
{

}
