#pragma once

#include "objects.h"
#include "control.h"

class AI : public Control, public Snake {
public:
    explicit AI();
    ~AI();

    void onControl() override;
    void onControl_v2() override;
};
