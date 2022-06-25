#pragma once

#include "objects.h"
#include "keypressable.h"

class Human : public Keypressable, public Snake {
public:
    explicit Human();
    ~Human();

    void onKey(char key) override;

private:
    void setDirection(Dir d);
};