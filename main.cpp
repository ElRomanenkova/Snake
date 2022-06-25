#include <cstdio>
#include <memory>

#include "ui.h"
#include "gui.h"

int main() {

    std::unique_ptr<View> view;
    std::string graf_type = "Gui";

    if (graf_type == "Gui") {
        view = std::make_unique<Gui>();
        View::setInst(view.get());
    }
    else {
        fprintf(stderr, "Cannot init View\n");
        return 0;
    }

    view->Run();

    return 0;
}