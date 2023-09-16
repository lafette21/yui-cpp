#include "yui/yui.h"

#include <fmt/format.h>

#include <cstdlib>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    fmt::print("Example {}\n", "project");

    try {
        yui::gui gui{"Yui", yui::gui_config{ yui::vec2{ 1280, 720 }}};

        gui.run([&gui] {
            gui.main_menu().menu("Foo");
        });
    } catch (const std::exception& ex) {
        fmt::print("Exception occured: {}", ex.what());
    }

    return EXIT_SUCCESS;
}
