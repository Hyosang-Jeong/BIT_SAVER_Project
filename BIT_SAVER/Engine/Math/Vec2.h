/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.h
Author: 
Creation date: 2021-03-13
-----------------------------------------------------------------*/
#pragma once
#include <cmath> //sqrt
#include <limits> //numeric limits

namespace math
{
    [[nodiscard]] constexpr double abs(double d) noexcept { return (d < 0.0) ? -d : d; }

    [[nodiscard]] constexpr bool is_equal(double d1, double d2) noexcept
    {
        return abs(d1 - d2) <= std::numeric_limits<double>::epsilon() * abs(d1 + d2);
    }

    [[nodiscard]] constexpr bool is_equal(int i1, int i2) noexcept { return i1 == i2; }

    struct [[nodiscard]] vec2
    {
        double x{ 0 }, y{ 0 };
        constexpr vec2() noexcept = default;
        constexpr vec2(double x_value, double y_value) noexcept : x{ x_value }, y{ y_value }{}

        constexpr vec2& operator+=(vec2 right) noexcept;
        constexpr vec2& operator-=(vec2 right) noexcept;
        constexpr vec2& operator*=(double value) noexcept;
        constexpr vec2& operator/=(double value) noexcept;
        [[nodiscard]] constexpr double LengthSquared() const noexcept;
        [[nodiscard]] inline vec2 Normalize() const noexcept;
        constexpr double Cross(const vec2& v) const noexcept;
    };


    struct [[nodiscard]] ivec2
    {
        int x{ 0 }, y{ 0 };
        constexpr ivec2() noexcept = default;
        constexpr ivec2(int x_value, int y_value) noexcept : x{ x_value }, y{ y_value }{}

        constexpr ivec2& operator+=(ivec2 right) noexcept;
        constexpr ivec2& operator-=(ivec2 right) noexcept;
        constexpr ivec2& operator*=(int value) noexcept;
        constexpr ivec2& operator/=(int value) noexcept;
        [[nodiscard]] constexpr operator vec2() noexcept;
    };

    [[nodiscard]] constexpr  vec2 operator+(vec2 left, vec2 right) noexcept;
    [[nodiscard]] constexpr  ivec2 operator+(ivec2 left, ivec2 right) noexcept;

    [[nodiscard]] constexpr  vec2 operator-(vec2 left, vec2 right) noexcept;
    [[nodiscard]] constexpr  vec2 operator-(vec2 value) noexcept;    //negate

    [[nodiscard]] constexpr  ivec2 operator-(ivec2 left, ivec2 right) noexcept;
    [[nodiscard]] constexpr  ivec2 operator-(ivec2 value) noexcept;  //negate

    [[nodiscard]] constexpr  vec2 operator*(vec2 vec, double value) noexcept;
    [[nodiscard]] constexpr  vec2 operator*(double value, vec2 vec) noexcept;
    [[nodiscard]] constexpr  vec2 operator*(double value, ivec2 vec) noexcept;
    [[nodiscard]] constexpr  vec2 operator*(ivec2 vec, double value) noexcept;

    [[nodiscard]] constexpr  ivec2 operator*(ivec2 vec, int value) noexcept;
    [[nodiscard]] constexpr  ivec2 operator*(int value, ivec2 vec) noexcept;

    [[nodiscard]] constexpr  vec2 operator/(vec2 vec, double value) noexcept;
    [[nodiscard]] constexpr  vec2 operator/(ivec2 vec, double value) noexcept;

    [[nodiscard]] constexpr  ivec2 operator/(ivec2 vec, int value) noexcept;

    [[nodiscard]] constexpr  bool operator==(vec2 value1, vec2 value2) noexcept;
    [[nodiscard]] constexpr  bool operator!=(vec2 value1, vec2 value2) noexcept;

    [[nodiscard]] constexpr  bool operator==(ivec2 value1, ivec2 value2) noexcept;
    [[nodiscard]] constexpr  bool operator!=(ivec2 value1, ivec2 value2) noexcept;
}

#include "Vec2.inl"
