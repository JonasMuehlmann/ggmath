#ifndef GG_MATH_VEC_HPP
#define GG_MATH_VEC_HPP
#include <algorithm>
#include <array>
#include <cmath>
#include <initializer_list>
#include <numeric>
#include <ostream>

#include "concepts.hpp"

// region macros


// NOLINTNEXTLINE(cppcoreguidelines-macro-usage,-warnings-as-errors)
#define COMMON_MEMBERS(n)                                                                              \
    constexpr explicit vec()                                                                           \
    {                                                                                                  \
        data.fill(0);                                                                                  \
    }                                                                                                  \
    /*NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)*/ \
    constexpr explicit vec(T(&_data)[n])                                                               \
    {                                                                                                  \
        data = std::to_array(_data);                                                                   \
    }                                                                                                  \
    constexpr vec(const vec& other) : data(other.data) {}                                              \
    constexpr vec(const vec&& other) noexcept : data(std::move(other.data)) {}                         \
                                                                                                       \
    constexpr vec(std::initializer_list<T> _data) : data(_data) {}                                     \
                                                                                                       \
    constexpr vec& operator=(const vec& other)                                                         \
    {                                                                                                  \
        if (this == &other)                                                                            \
            return *this;                                                                              \
                                                                                                       \
        data = other.data;                                                                             \
        return *this;                                                                                  \
    }                                                                                                  \
    constexpr vec& operator=(vec&& other) noexcept                                                     \
    {                                                                                                  \
        if (this == &other)                                                                            \
            return *this;                                                                              \
                                                                                                       \
        data = std::move(other.data);                                                                  \
        return *this;                                                                                  \
    }                                                                                                  \
    constexpr T operator[](size_t i) const                                                             \
    {                                                                                                  \
        return data[i];                                                                                \
    }                                                                                                  \
    ~vec() = default;


// endregion macros


namespace ggmath::vec
{
    // region classes


    template <typename T, int n>
    struct vec
    {
        std::array<T, n> data;
        COMMON_MEMBERS(n)
    };
    template <typename T>
    struct vec<T, 2>
    {
        union
        {
            std::array<T, 2> data;
            struct
            {
                T x, y;
            };
        };
        COMMON_MEMBERS(2)


        // region constructors


        constexpr explicit vec(T xy) : data{xy, xy} {}
        constexpr vec(T x, T y) : data{x, y} {}


        // endregion constructors
    };
    template <typename T>
    struct vec<T, 3>
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-union-access)
        union
        {
            std::array<T, 3> data;
            struct
            {
                T x, y, z;
            };
            struct
            {
                T r, g, b;
            };
        };
        COMMON_MEMBERS(3)


        // region constructors


        constexpr explicit vec(T xyz) : data{xyz, xyz, xyz} {}
        constexpr vec(T x, T y, T z) : data{x, y, z} {}
        constexpr vec(const vec<T, 2>& vec, T z) : data{vec.x, vec.y, z} {}


        // endregion constructors
    };
    // TODO: Find out how to correctly handle fourth component
    template <typename T>
    struct vec<T, 4>
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-union-access)
        union
        {
            std::array<T, 4> data;
            struct
            {
                T x, y, z, w;
            };
            struct
            {
                T r, g, b, a;
            };
        };
        COMMON_MEMBERS(4);


        // region constructors


        constexpr explicit vec(T xyzw) : data{xyzw, xyzw, xyzw, xyzw} {}
        constexpr vec(T xyz, T w) : data{xyz, xyz, xyz, w} {}
        constexpr vec(T x, T y, T z, T w) : data{x, y, z, w} {}
        constexpr vec(const vec<T, 3>& other, T w) :
            data{other[0], other[1], other[2], w}
        {}


        // endregion constructors
    };


    // endregion classes


    // region named constructors


    template <typename T, int n>
    constexpr vec<T, n> unit_x() noexcept
    {
        vec vector = vec<T, n>();
        vector[0]  = 1;
        return vector;
    }
    template <typename T, int n>
    constexpr vec<T, n> unit_y() noexcept
    {
        vec vector = vec<T, n>();
        vector[1]  = 1;
        return vector;
    }
    template <typename T, int n>
    constexpr vec<T, n> unit_z() noexcept
    {
        vec vector = vec<T, n>();
        vector[2]  = 1;
        return vector;
    }


    // endregion named constructors


    // region functions


    template <typename T>
    constexpr vec<T, 3> cross(const vec<T, 3>& a, const vec<T, 3>& b)
    {
        return vec<T, 3>(a[1] * b[2] - a[2] * b[1],
                         a[2] * b[0] - a[0] * b[2],
                         a[0] * b[1] - a[1] * b[0]);
    }
    template <typename T, int n>
    constexpr float length(const vec<T, n>& vec)
    {
        if (vec == ggmath::vec::vec<T, 3>())
        {
            return 0;
        }
        return abs(std::sqrt(vec * vec));
    }
    template <typename T, int n>
    constexpr float length_squared(const vec<T, n>& vec)
    {
        if (vec == ggmath::vec::vec<T, 3>())
        {
            return 0;
        }
        return vec * vec;
    }
    template <typename T, int n>
    constexpr vec<T, n> normalized(const vec<T, n>& vec)
    {
        return vec / length(vec);
    }
    template <typename T, int n>
    constexpr vec<T, n> scaled_by(const vec<T, n>& vec, float factor)
    {
        return vec * factor;
    }
    template <typename T, int n>
    constexpr vec<T, n> scaled_to(const vec<T, n>& vec, float wanted_magnitude)
    {
        float factor = wanted_magnitude / length(vec);

        if (!std::isnormal(factor))
        {
            return ggmath::vec::vec<T, n>();
        }
        return scaled_by(vec, factor);
    }
    template <typename T, int n>
    constexpr float distance(const vec<T, n>& a, const vec<T, n>& b)
    {
        return length((a - b));
    }
    template <typename T, int n>
    constexpr bool parallel(const vec<T, n>& a, const vec<T, n>& b)
    {
        return a * b == 1;
    }
    template <typename T, int n>
    constexpr bool anti_parallel(const vec<T, n>& a, const vec<T, n>& b)
    {
        return a * b == -1;
    }
    template <typename T, int n>
    constexpr bool perpendicular(const vec<T, n>& a, const vec<T, n>& b)
    {
        return std::abs(a * b) <= std::numeric_limits<float>::epsilon();
    }
    template <typename T, int n>
    constexpr float angle_between(const vec<T, n>& a, const vec<T, n>& b)
    {
        return std::acos((a * b) / (std::abs(length(a)) * std::abs(length(b))));
    }
    template <typename T, int n>
    constexpr bool is_unit_vector(const vec<T, n>& vec)
    {
        return length(vec) == 1;
    }
    template <typename T, int n>
    constexpr T min(const vec<T, n>& vec)
    {
        return *std::min_element(std::begin(vec.data), std::end(vec.data));
    }
    template <typename T, int n>
    constexpr T max(const vec<T, n>& vec)
    {
        return *std::max_element(std::begin(vec.data), std::end(vec.data));
    }
    template <typename T, int n>
    constexpr size_t index_min(const vec<T, n>& vec)
    {
        return std::distance(
            std::begin(vec.data),
            std::min_element(std::begin(vec.data), std::end(vec.data)));
    }
    template <typename T, int n>
    constexpr size_t index_max(const vec<T, n>& vec)
    {
        return std::distance(
            std::begin(vec.data),
            std::max_element(std::begin(vec.data), std::end(vec.data)));
    }
    template <typename T, int n>
    constexpr vec<T, n> lerp(const vec<T, n>& a, const vec<T, n>& b, float t)
    {
        return a + t * (b - a);
    }
    template <typename T, int n>
    constexpr vec<T, n> reflect(const vec<T, n>& a, const vec<T, n>& normal)
    {
        return a - 2 * (a * normal) * normal;
    }


    // endregion functions


    // region operator overloads


    template <typename T, int n>
    // Invert vector
    constexpr vec<T, n> operator-(const vec<T, n>& a)
    {
        vec<T, n> vector;
        std::transform(std::begin(a.data),
                       std::end(a.data),
                       std::begin(vector.data),
                       std::negate<T>());
        return vector;
    }


    // region binary operators


    // region vector-vector


    // Dot product
    template <typename T, int n>
    constexpr float operator*(const vec<T, n>& a, const vec<T, n>& b)
    {
        return std::inner_product(
            std::begin(a.data), std::end(a.data), std::begin(b.data), 0.0);
    }
    // Cross product
    template <typename T, int n>
    constexpr vec<T, n> operator%(const vec<T, n>& a, const vec<T, n>& b)
    {
        return cross(a, b);
    }
    // Vector-vector  addition
    template <typename T, int n>
    constexpr vec<T, n> operator+(const vec<T, n>& a, vec<T, n> b)
    {
        std::transform(std::begin(a.data),
                       std::end(a.data),
                       std::begin(b.data),
                       std::begin(b.data),
                       std::plus<T>());
        return b;
    }
    // Vector-vector subtraction
    template <typename T, int n>
    constexpr vec<T, n> operator-(const vec<T, n>& a, vec<T, n> b)
    {
        std::transform(std::begin(a.data),
                       std::end(a.data),
                       std::begin(b.data),
                       std::begin(b.data),
                       std::minus<T>());
        return b;
    }


    // endregion vector-vector


    // region scalar-vector


    // Scalar-vector multiplication
    template <typename T, int n>
    constexpr vec<T, n> operator*(const float scalar, vec<T, n> vec)
    {
        std::transform(std::begin(vec.data),
                       std::end(vec.data),
                       std::begin(vec.data),
                       [scalar](T element) { return element * scalar; });
        return vec;
    }
    // Scalar-vector multiplication
    template <typename T, int n>
    constexpr vec<T, n> operator*(const vec<T, n>& vec, const float scalar)
    {
        return scalar * vec;
    }
    // Scalar-vector division
    template <typename T, int n>
    constexpr vec<T, n> operator/(const float scalar, vec<T, n> vec)
    {
        std::transform(std::begin(vec.data),
                       std::end(vec.data),
                       std::begin(vec.data),
                       [scalar](T element) { return element / scalar; });
        return vec;
    }
    // Scalar-vector division
    template <typename T, int n>
    constexpr vec<T, n> operator/(const vec<T, n>& vec, const float scalar)
    {
        return scalar / vec;
    }


    // endregion scalar-vector


    // endregion binary operators


    // region assignment operators


    // region scalar-vector


    // Scalar-vector multiplication assignment
    template <typename T, int n>
    constexpr vec<T, n>& operator*=(vec<T, n>& vec, const float scalar)
    {
        std::transform(std::begin(vec.data),
                       std::end(vec.data),
                       std::begin(vec.data),
                       [scalar](T element) { return element * scalar; });
        return vec;
    }

    // Scalar-vector division assignment
    template <typename T, int n>
    constexpr vec<T, n>& operator/=(vec<T, n>& vec, const float scalar)
    {
        std::transform(std::begin(vec.data),
                       std::end(vec.data),
                       std::begin(vec.data),
                       [scalar](T element) { return element / scalar; });
        return vec;
    }


    // endregion scalar-vector


    // region vector-vector


    // Vector-vector addition-assignment
    template <typename T, int n>
    constexpr vec<T, n>& operator+=(vec<T, n>& a, const vec<T, n>& b)
    {
        std::transform(std::begin(a.data),
                       std::end(a.data),
                       std::begin(b.data),
                       std::begin(a.data),
                       std::plus<T>());
        return a;
    }
    // Vector-vector subtraction-assignment
    template <typename T, int n>
    constexpr vec<T, n>& operator-=(vec<T, n>& a, const vec<T, n>& b)
    {
        std::transform(std::begin(a.data),
                       std::end(a.data),
                       std::begin(b.data),
                       std::begin(a.data),
                       std::minus<T>());
        return a;
    }


    // endregion vector-vector


    // endregion assignment operators


    // region comparison operators


    // region vector-vector


    // Compare component-wise equality
    template <typename T, int n>
    constexpr bool operator==(const vec<T, n>& a, const vec<T, n>& b)
    {
        return std::equal(
            std::begin(a.data), std::end(a.data), std::begin(b.data), std::end(b.data));
    }

    // Compare component-wise equality
    template <typename T, int n>
    constexpr bool operator!=(const vec<T, n>& a, const vec<T, n>& b)
    {
        return !std::equal(
            std::begin(a.data), std::end(a.data), std::begin(b.data), std::end(b.data));
    }

    // Compare length
    template <typename T, int n>
    constexpr bool operator>(const vec<T, n>& a, const vec<T, n>& b)
    {
        return length(a) > length(b);
    }
    // Compare length
    template <typename T, int n>
    constexpr bool operator<(const vec<T, n>& a, const vec<T, n>& b)
    {
        return length(a) < length(b);
    }
    // Compare length
    template <typename T, int n>
    constexpr bool operator>=(const vec<T, n>& a, const vec<T, n>& b)
    {
        return length(a) >= length(b);
    }
    // Compare length
    template <typename T, int n>
    constexpr bool operator<=(const vec<T, n>& a, const vec<T, n>& b)
    {
        return length(a) <= length(b);
    }


    // endregion vector-vector


    // region scalar-vector


    // Compare length
    template <ggmath::Scalar T_Vec, ggmath::Scalar T_Scalar, int n>
    requires std::equality_comparable_with<T_Vec, T_Scalar> constexpr bool operator==(
        const vec<T_Vec, n>& vec, T_Scalar scalar)
    {
        return length(vec) == scalar;
    }

    // Compare length
    template <ggmath::Scalar T_Vec, ggmath::Scalar T_Scalar, int n>
    requires std::equality_comparable_with<T_Vec, T_Scalar> constexpr bool operator==(
        T_Scalar scalar, const vec<T_Vec, n>& vec)
    {
        return length(vec) == scalar;
    }

    // Compare length
    template <ggmath::Scalar T_Vec, ggmath::Scalar T_Scalar, int n>
    requires std::equality_comparable_with<T_Vec, T_Scalar> constexpr bool operator!=(
        const vec<T_Vec, n>& vec, T_Scalar scalar)
    {
        return length(vec) != scalar;
    }
    // Compare length
    template <ggmath::Scalar T_Vec, ggmath::Scalar T_Scalar, int n>
    requires std::equality_comparable_with<T_Vec, T_Scalar> constexpr bool operator!=(
        T_Scalar scalar, const vec<T_Vec, n>& vec)
    {
        return length(vec) != scalar;
    }

    // Compare length
    template <ggmath::Scalar T_Vec, ggmath::Scalar T_Scalar, int n>
    requires std::totally_ordered_with<T_Vec, T_Scalar> constexpr bool operator>(
        const vec<T_Vec, n>& vec, T_Scalar scalar)
    {
        return length(vec) > scalar;
    }
    // Compare length
    template <ggmath::Scalar T_Vec, ggmath::Scalar T_Scalar, int n>
    requires std::totally_ordered_with<T_Vec, T_Scalar> constexpr bool operator>(
        T_Scalar scalar, const vec<T_Vec, n>& vec)
    {
        return length(vec) > scalar;
    }

    // Compare length
    template <ggmath::Scalar T_Vec, ggmath::Scalar T_Scalar, int n>
    requires std::totally_ordered_with<T_Vec, T_Scalar> constexpr bool operator<(
        const vec<T_Vec, n>& vec, T_Scalar scalar)
    {
        return length(vec) < scalar;
    }
    // Compare length
    template <ggmath::Scalar T_Vec, ggmath::Scalar T_Scalar, int n>
    requires std::totally_ordered_with<T_Vec, T_Scalar> constexpr bool operator<(
        T_Scalar scalar, const vec<T_Vec, n>& vec)
    {
        return length(vec) < scalar;
    }

    // Compare length
    template <ggmath::Scalar T_Vec, ggmath::Scalar T_Scalar, int n>
    requires std::totally_ordered_with<T_Vec, T_Scalar> constexpr bool operator>=(
        const vec<T_Vec, n>& vec, T_Scalar scalar)
    {
        return length(vec) >= scalar;
    }
    // Compare length
    template <ggmath::Scalar T_Vec, ggmath::Scalar T_Scalar, int n>
    requires std::totally_ordered_with<T_Vec, T_Scalar> constexpr bool operator>=(
        T_Scalar scalar, const vec<T_Vec, n>& vec)
    {
        return length(vec) >= scalar;
    }

    // Compare length
    template <ggmath::Scalar T_Vec, ggmath::Scalar T_Scalar, int n>
    requires std::totally_ordered_with<T_Vec, T_Scalar> constexpr bool operator<=(
        const vec<T_Vec, n>& vec, T_Scalar scalar)
    {
        return length(vec) <= scalar;
    }
    // Compare length
    template <ggmath::Scalar T_Vec, ggmath::Scalar T_Scalar, int n>
    requires std::totally_ordered_with<T_Vec, T_Scalar> constexpr bool operator<=(
        T_Scalar scalar, const vec<T_Vec, n>& vec)
    {
        return length(vec) <= scalar;
    }


    // endregion scalar-vector


    // endregion comparison operators


    // Format: (data[0],data[2],...,data[n])
    template <typename T, int n>
    constexpr std::ostream& operator<<(std::ostream& os, const vec<T, n>& vec)
    {
        const auto last = std::end(vec.data) - 1;

        os << '(';
        // Loop ends before last
        std::for_each(
            std::begin(vec.data), last, [&os](T element) { os << element << ','; });
        os << *last;
        os << ')';

        return os;
    }


    // endregion operator overloads


    using vec2f  = vec<float, 2>;
    using vec3f  = vec<float, 3>;
    using vec4f  = vec<float, 4>;
    using color3 = vec<u_int8_t, 3>;
    using color4 = vec<u_int8_t, 4>;
};        // namespace ggmath::vec
#endif    // GG_MATH_VEC_HPP
