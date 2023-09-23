#ifndef TYPES_H
#define TYPES_H

#include <imgui.h>

#include <array>

#define NOVA_EXTENSION_CLASS_VEC2                                               \
    constexpr vec2(ImVec2 obj)                                                  \
        : vec_type(std::to_array({ obj.x, obj.y, }))                            \
    {}                                                                          \
    constexpr operator ImVec2() const {                                         \
        return { x(), y() };                                                    \
    }                                                                           \

#include <nova/color.h>
#include <nova/vec.h>

#include <compare>

namespace yui {

using nova::Vec2f;
using nova::Color;

} // namespace yui

#endif // TYPES_H
