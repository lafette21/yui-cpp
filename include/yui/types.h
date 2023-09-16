#ifndef TYPES_H
#define TYPES_H

#include <imgui.h>

#include <algorithm>
#include <cstdint>
#include <compare>
#include <type_traits>

namespace yui {

template <class T>
concept arithmetic = std::is_arithmetic_v<T>;

/**
 * @brief   Internal vec2 type
 */
struct vec2 {
    constexpr vec2() = default;
    constexpr vec2(float x, float y):
        data{ x, y }
    {}
    constexpr vec2(ImVec2 obj):
        data{ obj.x, obj.y }
    {}

    constexpr auto operator<=>(const vec2&) const = default;

    constexpr inline vec2& operator+=(const vec2& obj) noexcept {
        data[0] += obj.data[0];
        data[1] += obj.data[1];
        return *this;
    }

    /**
     * @brief   Division by a scalar
     */
    constexpr inline vec2& operator/=(float scalar) noexcept {
        data[0] /= scalar;
        data[1] /= scalar;
        return *this;
    }

    operator ImVec2() const {
        return { data[0], data[1] };
    }

    constexpr float& x() { return data[0]; }
    constexpr float& y() { return data[1]; }

    constexpr float x() const { return data[0]; }
    constexpr float y() const { return data[1]; }

    float data[2];
};

constexpr inline vec2 operator+(const vec2& lhs, const vec2& rhs) noexcept {
    return {
        lhs.data[0] + rhs.data[0],
        lhs.data[1] + rhs.data[1]
    };
}

constexpr inline vec2 operator+(const ImVec2& lhs, const vec2& rhs) noexcept {
    return {
        lhs.x + rhs.data[0],
        lhs.y + rhs.data[1]
    };
}

constexpr inline vec2 operator+(const vec2& lhs, const ImVec2& rhs) noexcept {
    return rhs + lhs;
}

constexpr inline vec2 operator-(const vec2& lhs, const vec2& rhs) noexcept {
    return {
        lhs.data[0] - rhs.data[0],
        lhs.data[1] - rhs.data[1]
    };
}

constexpr inline vec2 operator-(const ImVec2& lhs, const vec2& rhs) noexcept {
    return {
        lhs.x - rhs.data[0],
        lhs.y - rhs.data[1]
    };
}

constexpr inline vec2 operator-(const vec2& lhs, const ImVec2& rhs) noexcept {
    return rhs - lhs;
}

/**
 * @brief:   Element-wise multiplication
 */
constexpr inline vec2 operator*(const vec2& lhs, const vec2& rhs) noexcept {
    return {
        lhs.data[0] * rhs.data[0],
        lhs.data[1] * rhs.data[1]
    };
}

/**
 * @brief   Element-wise division
 */
constexpr inline vec2 operator/(const vec2& lhs, const vec2& rhs) noexcept {
    return {
        lhs.data[0] / rhs.data[0],
        lhs.data[1] / rhs.data[1]
    };
}

/**
 * @brief   Division by a scalar
 */
constexpr inline vec2 operator/(const vec2& lhs, float rhs) noexcept {
    return {
        lhs.data[0] / rhs,
        lhs.data[1] / rhs
    };
}

/**
 * @brief   Internal vec4 type
 */
struct vec4 {
    constexpr float x() const { return data[0]; }
    constexpr float y() const { return data[1]; }
    constexpr float z() const { return data[2]; }
    constexpr float w() const { return data[3]; }

    constexpr float r() const { return data[0]; }
    constexpr float g() const { return data[1]; }
    constexpr float b() const { return data[2]; }
    constexpr float a() const { return data[3]; }

    float data[4];
};

namespace color {
    constexpr auto black = vec4{   0.0f,   0.0f,   0.0f, 255.0f };
    constexpr auto white = vec4{ 255.0f, 255.0f, 255.0f, 255.0f };
    constexpr auto blue  = vec4{   0.0f,   0.0f, 255.0f, 255.0f };
}

/**
 * @brief   Clamp between 0 and 255 for packing four 8-bit values
 */
[[nodiscard]] constexpr uint32_t cast8(arithmetic auto x) noexcept {
    return std::clamp(static_cast<uint32_t>(x), 0u, 255u);
}

/**
 * @brief   Pack 4 8-bit values (Little endian)
 */
template <arithmetic T>
[[nodiscard]] constexpr std::uint32_t pack32LE(T x, T y, T z, T w) noexcept {
    return cast8(w) << 24
         | cast8(z) << 16
         | cast8(y) << 8
         | cast8(x);
}

/**
 * @brief   Pack 4 8-bit values (Big endian)
 */
template <arithmetic T>
[[nodiscard]] constexpr std::uint32_t pack32BE(T x, T y, T z, T w) noexcept {
    return pack32LE(w, z, y, x);
}

constexpr inline auto area(vec2 dimensions) noexcept {
    return dimensions.x() * dimensions.y();
}

[[nodiscard]] constexpr std::uint32_t pack32LE(vec4 value) noexcept {
    return pack32LE(
        value.x(),
        value.y(),
        value.z(),
        value.w()
    );
}

[[nodiscard]] constexpr std::uint32_t pack32BE(vec4 value) noexcept {
    return pack32BE(
        value.x(),
        value.y(),
        value.z(),
        value.w()
    );
}


} // namespace yui

#endif // TYPES_H
