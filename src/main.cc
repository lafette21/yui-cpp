#include "yui/yui.h"

#include <fmt/format.h>

#include <cstdlib>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    fmt::println("Example {}", "project");

    return EXIT_SUCCESS;
}
