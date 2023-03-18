#include <iostream>
#include <memory>

#include "core/application.h"

int main() {
    try {
        std::unique_ptr<vx::core::Application> application {new vx::core::Application};
        application->Run();
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}