#pragma once

class Control {
public:
    virtual ~Control() = default;
    virtual void onControl() = 0;
    virtual void onControl_v2() = 0;
};
