#pragma once

class OpenglVersion {
public:
    bool static Validate(int major, int minor);
    OpenglVersion(int major, int minor);

    int major;
    int minor;
};
