#include "yui/yui.h"

#include <fmt/format.h>

#include <cstdlib>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    fmt::print("Example {}\n", "project");

    try {
        yui::gui gui{"Yui", yui::gui_config{ yui::vec2{ 1280, 720 }, {}, {} }};

        int ivalue = 0;
        float fvalue = 0;

        gui.run([&] {
            gui.main_menu().menu("Foo");

            gui.window("Test")
                .slider("Slider1", &ivalue, -100, 100)
                .drag_slider("DragSlider1", &fvalue, 1.0f, -100.0f, 100.0f);
        });
    } catch (const std::exception& ex) {
        fmt::print("Exception occured: {}\n", ex.what());
    }

    return EXIT_SUCCESS;
}
