#ifndef TYPES_H
#define TYPES_H

#include <imgui.h>

#define NOVA_VEC2_EXTRA                                                         \
    constexpr vec2(ImVec2 obj)                                                  \
        : vec_type(std::to_array({ obj.x, obj.y, }))                            \
    {}                                                                          \
    constexpr operator ImVec2() const {                                         \
        return { x(), y() };                                                    \
    }                                                                           \

#include <nova/vec.h>

#include <compare>

namespace yui {

using namespace nova;

namespace color {
    constexpr auto black = Vec4f{   0.0f,   0.0f,   0.0f, 255.0f };
    constexpr auto white = Vec4f{ 255.0f, 255.0f, 255.0f, 255.0f };
}

} // namespace yui

#endif // TYPES_H
