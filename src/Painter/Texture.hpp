#pragma once

#include <memory>
#include <string>

class Texture {
public:
    virtual void Use() = 0;
    virtual ~Texture() = default;

protected:
    std::unique_ptr<char[]> Load(const std::string &path);
    std::unique_ptr<char[]> Text(const std::string &str);
};

typedef std::unique_ptr<Texture> TexturePtr;
