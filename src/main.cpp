#include <iostream>

#include "core/window.h"

int main() {
    vx::core::Window window{800, 600, "VisionX"};

    while (!window.ShouldClose())
    {
        window.Update();
    }

    return 0;
}