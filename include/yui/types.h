#ifndef TYPES_H
#define TYPES_H

#include <imgui.h>

#include <compare>

namespace yui {

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

    auto operator<=>(const vec2&) const = default;

    inline vec2& operator+=(const vec2& obj) noexcept {
        data[0] += obj.data[0];
        data[1] += obj.data[1];
        return *this;
    }

    /**
     * @brief   Division by a scalar
     */
    inline vec2& operator/=(float scalar) noexcept {
        data[0] /= scalar;
        data[1] /= scalar;
        return *this;
    }

    operator ImVec2() const {
        return { data[0], data[1] };
    }

    float& x() { return data[0]; }
    float& y() { return data[1]; }

    float x() const { return data[0]; }
    float y() const { return data[1]; }

    float data[2];
};

inline vec2 operator+(const vec2& lhs, const vec2& rhs) noexcept {
    return {
        lhs.data[0] + rhs.data[0],
        lhs.data[1] + rhs.data[1]
    };
}

inline vec2 operator+(const ImVec2& lhs, const vec2& rhs) noexcept {
    return {
        lhs.x + rhs.data[0],
        lhs.y + rhs.data[1]
    };
}

inline vec2 operator+(const vec2& lhs, const ImVec2& rhs) noexcept {
    return rhs + lhs;
}

inline vec2 operator-(const vec2& lhs, const vec2& rhs) noexcept {
    return {
        lhs.data[0] - rhs.data[0],
        lhs.data[1] - rhs.data[1]
    };
}

inline vec2 operator-(const ImVec2& lhs, const vec2& rhs) noexcept {
    return {
        lhs.x - rhs.data[0],
        lhs.y - rhs.data[1]
    };
}

inline vec2 operator-(const vec2& lhs, const ImVec2& rhs) noexcept {
    return rhs - lhs;
}

/**
 * @brief:   Element-wise multiplication
 */
inline vec2 operator*(const vec2& lhs, const vec2& rhs) noexcept {
    return {
        lhs.data[0] * rhs.data[0],
        lhs.data[1] * rhs.data[1]
    };
}

/**
 * @brief   Element-wise division
 */
inline vec2 operator/(const vec2& lhs, const vec2& rhs) noexcept {
    return {
        lhs.data[0] / rhs.data[0],
        lhs.data[1] / rhs.data[1]
    };
}

/**
 * @brief   Division by a scalar
 */
inline vec2 operator/(const vec2& lhs, float rhs) noexcept {
    return {
        lhs.data[0] / rhs,
        lhs.data[1] / rhs
    };
}

/**
 * @brief   Internal vec4 type
 */
struct vec4 {
    float x() const { return data[0]; }
    float y() const { return data[1]; }
    float z() const { return data[2]; }
    float w() const { return data[3]; }

    float r() const { return data[0]; }
    float g() const { return data[1]; }
    float b() const { return data[2]; }
    float a() const { return data[3]; }

    float data[4];
};

namespace color {
    constexpr auto black = vec4{   0.0f,   0.0f,   0.0f, 255.0f };
    constexpr auto white = vec4{ 255.0f, 255.0f, 255.0f, 255.0f };
}

} // namespace yui

#endif // TYPES_H
