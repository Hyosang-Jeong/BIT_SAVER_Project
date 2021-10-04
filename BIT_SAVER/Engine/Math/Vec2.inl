/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.inl
Author: Hyosang Jung
Creation date: 2021-03-13
-----------------------------------------------------------------*/

namespace math
{
    [[nodiscard]] constexpr vec2 operator+(vec2 left, vec2 right) noexcept
    {
        vec2 add_value;
        add_value.x = left.x + right.x;
        add_value.y = left.y + right.y;
        return add_value;
    }
    [[nodiscard]] constexpr vec2 operator-(vec2 left, vec2 right) noexcept
    {
        vec2 sub_value;
        sub_value.x = left.x - right.x;
        sub_value.y = left.y - right.y;
        return sub_value;
    }
    [[nodiscard]] constexpr  vec2 operator-(vec2 value) noexcept    //negate
    {
        vec2 negate_value;
        negate_value.x = value.x * -1;
        negate_value.y = value.y * -1;
        return negate_value;
    }

    [[nodiscard]] constexpr vec2 operator*(vec2 vec, double value) noexcept
    {
        vec2 scale_value;
        scale_value.x = vec.x * value;
        scale_value.y = vec.y * value;
        return scale_value;
    }
    [[nodiscard]] constexpr  vec2 operator*(double value, vec2 vec) noexcept
    {
        vec2 scale_value;
        scale_value.x = vec.x * value;
        scale_value.y = vec.y * value;
        return scale_value;
    }
    [[nodiscard]] constexpr  vec2 operator*(double value, ivec2 vec) noexcept
    {
        vec2 scale_value;
        scale_value.x = vec.x * value;
        scale_value.y = vec.y * value;
        return scale_value;
    }
    [[nodiscard]] constexpr  vec2 operator*(ivec2 vec, double value) noexcept
    {
        vec2 scale_value;
        scale_value.x = vec.x * value;
        scale_value.y = vec.y * value;
        return scale_value;
    }
    [[nodiscard]] constexpr  vec2 operator/(vec2 vec, double value) noexcept
    {
        vec2 divide_value;
        divide_value.x = vec.x / value;
        divide_value.y = vec.y / value;
        return divide_value;
    }
    [[nodiscard]] constexpr  vec2 operator/(ivec2 vec, double value) noexcept
    {
        vec2 divide_value;
        divide_value.x = vec.x / value;
        divide_value.y = vec.y / value;
        return divide_value;
    }
    [[nodiscard]] constexpr  bool operator==(vec2 value1, vec2 value2) noexcept
    {
        bool x_check = math::is_equal(value1.x, value2.x);
        bool y_check = math::is_equal(value1.y, value2.y);
        if (x_check == true && y_check == true)
        {
            return true;
        }
        return false;
    }
    [[nodiscard]] constexpr  bool operator!=(vec2 value1, vec2 value2) noexcept
    {
        bool x_check = math::is_equal(value1.x, value2.x);
        bool y_check = math::is_equal(value1.y, value2.y);
        if (x_check == true && y_check == true)
        {
            return false;
        }
        return true;
    }
    constexpr vec2& vec2::operator+=(vec2 right) noexcept
    {
        *this = *this + right;
        return *this;
    }
    constexpr vec2& vec2::operator-=(vec2 right) noexcept
    {
        *this = *this - right;
        return *this;
    }
    constexpr vec2& vec2::operator*=(double value) noexcept
    {
        *this = *this * value;
        return *this;
    }
    constexpr vec2& vec2::operator/=(double value) noexcept
    {
        *this = *this / value;
        return *this;
    }
    inline vec2 vec2::Normalize() const noexcept
    {
        return *this / sqrt(LengthSquared());
    }
    [[nodiscard]] constexpr double vec2::LengthSquared() const noexcept
    {
        double len = (x * x + y * y);
        return len;
    }

    constexpr double vec2::Cross(const vec2& v) const noexcept
    {
        return  (x * v.y) - (y * v.x);
    }
    /*--------------------------------------------------------------------------*/

    [[nodiscard]] constexpr ivec2 operator+(ivec2 left, ivec2 right) noexcept
    {
        ivec2 add_value;
        add_value.x = left.x + right.x;
        add_value.y = left.y + right.y;
        return add_value;
    }
    [[nodiscard]] constexpr ivec2 operator-(ivec2 left, ivec2 right) noexcept
    {
        ivec2 add_value;
        add_value.x = left.x - right.x;
        add_value.y = left.y - right.y;
        return add_value;
    }
    [[nodiscard]] constexpr  ivec2 operator-(ivec2 value) noexcept
    {
        ivec2 negate_value;
        negate_value.x = value.x * -1;
        negate_value.y = value.y * -1;
        return negate_value;
    }
    [[nodiscard]] constexpr  ivec2 operator*(ivec2 vec, int value) noexcept
    {
        ivec2 scale_value;
        scale_value.x = vec.x * value;
        scale_value.y = vec.y * value;
        return scale_value;
    }
    [[nodiscard]] constexpr  ivec2 operator*(int value, ivec2 vec) noexcept
    {
        ivec2 scale_value;
        scale_value.x = vec.x * value;
        scale_value.y = vec.y * value;
        return scale_value;
    }
    [[nodiscard]] constexpr  ivec2 operator/(ivec2 vec, int value) noexcept
    {
        ivec2 divide_value;
        divide_value.x = vec.x / value;
        divide_value.y = vec.y / value;
        return divide_value;
    }
    [[nodiscard]] constexpr  bool operator==(ivec2 value1, ivec2 value2) noexcept
    {
        if ((value1.x == value2.x) && (value1.y == value2.y))
        {
            return true;
        }
        return false;
    }
    [[nodiscard]] constexpr  bool operator!=(ivec2 value1, ivec2 value2) noexcept
    {
        if ((value1.x == value2.x) && (value1.y == value2.y))
        {
            return false;
        }
        return true;
    }

    constexpr ivec2& ivec2::operator+=(ivec2 right) noexcept
    {
        *this = *this + right;
        return *this;
    }

    constexpr ivec2& ivec2::operator-=(ivec2 right) noexcept
    {
        *this = *this - right;
        return *this;
    }

    constexpr ivec2& ivec2::operator*=(int value) noexcept
    {
        *this = *this * value;
        return *this;
    }

    constexpr ivec2& ivec2::operator/=(int value) noexcept
    {
        *this = *this / value;
        return *this;
    }

    [[nodiscard]] constexpr ivec2::operator vec2() noexcept
    {
        return vec2(static_cast<double>(this->x), static_cast<double>(this->y));
    }
}
