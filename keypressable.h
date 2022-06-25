#pragma once

class Keypressable {
public:
    virtual ~Keypressable() = default;
    virtual void onKey(char key) = 0;
};