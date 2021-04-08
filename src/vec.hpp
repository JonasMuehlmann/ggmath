#ifndef GG_MATH_VEC_HPP
#define GG_MATH_VEC_HPP
#include <algorithm>
#include <array>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <stdexcept>

#include "concepts.hpp"

// region macros


// NOLINTNEXTLINE(cppcoreguidelines-macro-usage,-warnings-as-errors)
#define COMMON_MEMBERS(n)                                                                              \
                                                                                                       \
                                                                                                       \
    /* region macros::constructors */                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr explicit vec()                                                                           \
    {                                                                                                  \
        data.fill(0);                                                                                  \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    /*NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)*/ \
    constexpr explicit vec(T(&_data)[n])                                                               \
    {                                                                                                  \
        data = std::to_array(_data);                                                                   \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr vec(const vec& other) : data(other.data) {}                                              \
                                                                                                       \
                                                                                                       \
    constexpr vec(const vec&& other) noexcept : data(std::move(other.data)) {}                         \
                                                                                                       \
                                                                                                       \
    constexpr vec(std::initializer_list<T> _data) : data(_data) {}                                     \
                                                                                                       \
                                                                                                       \
    /* endregion macros::cnstructors */                                                                \
                                                                                                       \
                                                                                                       \
    /* region macros::ierators */                                                                      \
                                                                                                       \
                                                                                                       \
    constexpr auto begin() noexcept                                                                    \
    {                                                                                                  \
        return data.begin();                                                                           \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr auto begin() const noexcept                                                              \
    {                                                                                                  \
        return data.begin();                                                                           \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr auto end() noexcept                                                                      \
    {                                                                                                  \
        return data.end();                                                                             \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr auto end() const noexcept                                                                \
    {                                                                                                  \
        return data.end();                                                                             \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr auto cbegin() const noexcept                                                             \
    {                                                                                                  \
        return data.cbegin();                                                                          \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr auto cend() const noexcept                                                               \
    {                                                                                                  \
        return data.cend();                                                                            \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr auto rbegin() noexcept                                                                   \
    {                                                                                                  \
        return data.rbegin();                                                                          \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr auto rbegin() const noexcept                                                             \
    {                                                                                                  \
        return data.rbegin();                                                                          \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr auto rend() noexcept                                                                     \
    {                                                                                                  \
        return data.rend();                                                                            \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr auto rend() const noexcept                                                               \
    {                                                                                                  \
        return data.rend();                                                                            \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr auto crbegin() const noexcept                                                            \
    {                                                                                                  \
        return data.crbegin();                                                                         \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr auto crend() const noexcept                                                              \
    {                                                                                                  \
        return data.crend();                                                                           \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    /* endregion macros::iterators */                                                                  \
                                                                                                       \
                                                                                                       \
    /* region macros::other */                                                                         \
                                                                                                       \
                                                                                                       \
    constexpr vec& operator=(const vec& other)                                                         \
    {                                                                                                  \
        if (this == &other)                                                                            \
            return *this;                                                                              \
                                                                                                       \
        data = other;                                                                                  \
        return *this;                                                                                  \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr vec& operator=(vec&& other) noexcept                                                     \
    {                                                                                                  \
        if (this == &other)                                                                            \
            return *this;                                                                              \
                                                                                                       \
        data = std::move(other);                                                                       \
        return *this;                                                                                  \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr T& operator[](size_t i)                                                                  \
    {                                                                                                  \
        return data[i];                                                                                \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    constexpr const T& operator[](size_t i) const                                                      \
    {                                                                                                  \
        return data[i];                                                                                \
    }                                                                                                  \
                                                                                                       \
    ~vec() = default;                                                                                  \
                                                                                                       \
                                                                                                       \
    /* endregion macros::other */


// endregion macros


// region forward_declarations


// TODO: Check if these are really necessary
namespace ggmath::vec
{
    template <typename T, int n>
    struct vec;
}    // namespace ggmath::vec
namespace ggmath::debug
{
    template <typename T, int n>
    void throw_if_not_unit(const ggmath::vec::vec<T, n>& vec);
}    // namespace ggmath::debug


// endregion forward_declarations


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


        // region classes::constructors


        constexpr explicit vec(T xy) : data{xy, xy} {}


        constexpr vec(T x, T y) : data{x, y} {}


        // endregion classes::constructors
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


        // region classes::constructors


        constexpr explicit vec(T xyz) : data{xyz, xyz, xyz} {}

        constexpr vec(T x, T y, T z) : data{x, y, z} {}

        constexpr vec(const vec<T, 2>& vec, T z) : data{vec.x, vec.y, z} {}


        // endregion classes::constructors
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


        // region classes::constructors


        constexpr explicit vec(T xyzw) : data{xyzw, xyzw, xyzw, xyzw} {}

        constexpr vec(T xyz, T w) : data{xyz, xyz, xyz, w} {}

        constexpr vec(T x, T y, T z, T w) : data{x, y, z, w} {}

        constexpr vec(const vec<T, 3>& other, T w) :
            data{other[0], other[1], other[2], w}
        {}


        // endregion classes::constructors
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


    /**
     * @brief Calculate the cross product(a x b) of two vectors a and b
     */
    template <typename T>
    constexpr vec<T, 3> cross(const vec<T, 3>& a, const vec<T, 3>& b)
    {
        return vec<T, 3>(a[1] * b[2] - a[2] * b[1],
                         a[2] * b[0] - a[0] * b[2],
                         a[0] * b[1] - a[1] * b[0]);
    }


    /**
     * @brief Calculate the length of vec
     */
    template <typename T, int n>
    constexpr float length(const vec<T, n>& vec)
    {
        return abs(std::sqrt(vec * vec));
    }


    /**
     * @brief Calculate the squared length of vec
     *
     * This function is potentially faster than squaring the length after calculating it
     * (length(vec) * length(vec))
     */
    template <typename T, int n>
    constexpr float length_squared(const vec<T, n>& vec)
    {
        return vec * vec;
    }


    /**
     * @brief Return a copy of vec scaled to a length of 1
     */
    template <typename T, int n>
    constexpr vec<T, n> normalized(const vec<T, n>& vec)
    {
        return vec / length(vec);
    }


    /**
     * @brief Return a copy of vec with a length of length * factor
     *
     */
    template <typename T, int n>
    constexpr vec<T, n> scaled_by(const vec<T, n>& vec, float factor)
    {
        return vec * factor;
    }

    /**
     * @brief Return a copy of vec with a length of wanted_magnitude
     */
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

    /**
     * @brief Return the signed distance from a to b
     */
    template <typename T, int n>
    constexpr float distance(const vec<T, n>& a, const vec<T, n>& b)
    {
        return length((a - b));
    }

    /**
     * @brief Check whetever or not the unit-vectors a and b are parallel (point in the
     * same direction)
     *
     * If the vectors have a length other than 1, the result will be incorrect.
     * Define the macro GGMATH_DEBUG to throw an exception if one of the parameters is
     * NOT a unit-vector.
     */
    template <typename T, int n>
    constexpr bool parallel(const vec<T, n>& a, const vec<T, n>& b)
    {
#ifdef GGMATH_DEBUG
        ggmath::debug::check_unit_vector(a);
        ggmath::debug::check_unit_vector(b);
#endif
        return a * b == 1;
    }

    /**
     * @brief Check whetever or not the unit-vectors a and b are anti-parallel(point in
     * the opposite direction)
     *
     * If the vectors have a length other than 1, the result will be incorrect.
     * Define the macro GGMATH_DEBUG to throw an exception if one of the parameters is
     * NOT a unit-vector.
     */
    template <typename T, int n>
    constexpr bool anti_parallel(const vec<T, n>& a, const vec<T, n>& b)
    {
#ifdef GGMATH_DEBUG
        ggmath::debug::check_unit_vector(a);
        ggmath::debug::check_unit_vector(b);
#endif
        return a * b == -1;
    }

    /**
     * @brief Check whetever or not the unit-vectors a and b are perpendicular(the angle
     * between them is 90 deg)
     *
     * If the vectors have a length other than 1, the result will be incorrect.
     * Define the macro GGMATH_DEBUG to throw an exception if one of the parameters is
     * NOT a unit-vector.
     */
    template <typename T, int n>
    constexpr bool perpendicular(const vec<T, n>& a, const vec<T, n>& b)
    {
#ifdef GGMATH_DEBUG
        ggmath::debug::check_unit_vector(a);
        ggmath::debug::check_unit_vector(b);
#endif
        return std::abs(a * b) <= std::numeric_limits<float>::epsilon();
    }


    /**
     * @brief Return the angle between the vectors
     */
    template <typename T, int n>
    constexpr float angle_between(const vec<T, n>& a, const vec<T, n>& b)
    {
        return std::acos((a * b) / (std::abs(length(a)) * std::abs(length(b))));
    }

    /**
     * @brief Check if the given vector has a length of 1
     */
    template <typename T, int n>
    constexpr bool is_unit_vector(const vec<T, n>& vec)
    {
        return length(vec) == 1;
    }

    /**
     * @brief Return the smallest element in the vector
     */
    template <typename T, int n>
    constexpr T min(const vec<T, n>& vec)
    {
        return *std::ranges::min_element(vec);
    }

    /**
     * @brief Return the largest element in the vector
     */
    template <typename T, int n>
    constexpr T max(const vec<T, n>& vec)
    {
        return *std::ranges::max_element(vec);
    }

    /**
     * @brief Return the 0-based index of the smallest element in the vector
     */
    template <typename T, int n>
    constexpr size_t index_min(const vec<T, n>& vec)
    {
        return std::ranges::distance(std::begin(vec), std::ranges::min_element(vec));
    }

    /**
     * @brief Return the 0-based index of the largest element in the vector
     */
    template <typename T, int n>
    constexpr size_t index_max(const vec<T, n>& vec)
    {
        return std::ranges::distance(
            std::begin(vec), std::ranges::max_element(std::begin(vec), std::end(vec)));
    }


    /**
     * Return a vector that is the linear interpolation between a and b with a weight of
     * t
     */
    template <typename T, int n>
    constexpr vec<T, n> lerp(const vec<T, n>& a, const vec<T, n>& b, float t)
    {
        return a + t * (b - a);
    }


    /**
     * Reflect the vector a about normal
     * If the vectors have a length other than 1, the result will be incorrect.
     * Define the macro GGMATH_DEBUG to throw an exception if one of the parameters is
     * NOT a unit-vector.
     */
    template <typename T, int n>
    constexpr vec<T, n> reflect(const vec<T, n>& a, const vec<T, n>& normal)
    {
#ifdef GGMATH_DEBUG
        ggmath::debug::check_unit_vector(a);
        ggmath::debug::check_unit_vector(normal);
#endif
        return a - 2 * (a * normal) * normal;
    }


    // endregion functions


    // region operator_overloads


    // region operator_overloads::binary


    // region operator_overloads::binary::vector-vector


    // Dot product
    template <typename T, int n>
    constexpr float operator*(const vec<T, n>& a, const vec<T, n>& b)
    {
        return std::inner_product(std::begin(a), std::end(a), std::begin(b), 0.0);
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
        std::ranges::transform(a, b, std::begin(b), std::plus<T>());
        return b;
    }


    // Vector-vector subtraction
    template <typename T, int n>
    constexpr vec<T, n> operator-(const vec<T, n>& a, vec<T, n> b)
    {
        std::ranges::transform(a, b, std::begin(b), std::minus<T>());
        return b;
    }


    // endregion operator_overloads::binary::vector-vector


    // region operator_overloads::binary::scalar-vector


    // Scalar-vector multiplication
    template <typename T, int n>
    constexpr vec<T, n> operator*(const float scalar, vec<T, n> vec)
    {
        std::ranges::transform(
            vec, std::begin(vec), [scalar](T element) { return element * scalar; });
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
        std::ranges::transform(
            vec, std::begin(vec), [scalar](T element) { return element / scalar; });
        return vec;
    }


    // Scalar-vector division
    template <typename T, int n>
    constexpr vec<T, n> operator/(const vec<T, n>& vec, const float scalar)
    {
        return scalar / vec;
    }


    // endregion operator_overloads::binary::scalar-vector


    // endregion operator_overloads::binary


    // region operator_overloads::assignment


    // region operator_overloads::assignment::scalar-vector


    // Scalar-vector multiplication assignment
    template <typename T, int n>
    constexpr vec<T, n>& operator*=(vec<T, n>& vec, const float scalar)
    {
        std::ranges::transform(
            vec, std::begin(vec), [scalar](T element) { return element * scalar; });
        return vec;
    }

    // Scalar-vector division assignment
    template <typename T, int n>
    constexpr vec<T, n>& operator/=(vec<T, n>& vec, const float scalar)
    {
        std::ranges::transform(
            vec, std::begin(vec), [scalar](T element) { return element / scalar; });
        return vec;
    }


    // endregion operator_overloads::assignment::scalar-vector


    // region operator_overloads::assignment::vector-vector


    // Vector-vector addition-assignment
    template <typename T, int n>
    constexpr vec<T, n>& operator+=(vec<T, n>& a, const vec<T, n>& b)
    {
        std::ranges::transform(a, b, std::begin(a), std::plus<T>());
        return a;
    }


    // Vector-vector subtraction-assignment
    template <typename T, int n>
    constexpr vec<T, n>& operator-=(vec<T, n>& a, const vec<T, n>& b)
    {
        std::ranges::transform(a, b, std::begin(a), std::minus<T>());
        return a;
    }


    // endregion vector-vector


    // endregion operator_overloads::assignment


    // region operator_overloads::comparison


    // region operator_overloads::comparison::vector-vector


    // Compare component-wise equality
    template <typename T, int n>
    constexpr bool operator==(const vec<T, n>& a, const vec<T, n>& b)
    {
        return std::ranges::equal(a, b);
    }


    // Compare component-wise equality
    template <typename T, int n>
    constexpr bool operator!=(const vec<T, n>& a, const vec<T, n>& b)
    {
        return !std::ranges::equal(a, b);
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


    // endregion operator_overloads::comparison::vector-vector


    // region operator_overloads::comparison::scalar-vector


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


    // endregion operator_overloads::comparison::scalar-vector


    // endregion operator_overloads::comparison


    // region operator_overloads::other


    // Invert vector
    template <typename T, int n>
    constexpr vec<T, n> operator-(const vec<T, n>& a)
    {
        vec<T, n> vector;
        std::ranges::transform(
            std::begin(a), std::end(a), std::begin(vector), std::negate<T>());
        return vector;
    }


    // Format: (data[0],data[2],...,data[n])
    template <typename T, int n>
    constexpr std::ostream& operator<<(std::ostream& os, const vec<T, n>& vec)
    {
        const auto last = std::end(vec) - 1;

        os << '(';
        // Loop ends before last
        std::for_each(
            std::begin(vec), last, [&os](T element) { os << element << ','; });
        os << *last;
        os << ')';

        return os;
    }


    // endregion operator_overloads::other


    // endregion operator_overloads


    using vec2f  = vec<float, 2>;
    using vec3f  = vec<float, 3>;
    using vec4f  = vec<float, 4>;
    using color3 = vec<u_int8_t, 3>;
    using color4 = vec<u_int8_t, 4>;
};    // namespace ggmath::vec


namespace ggmath::debug
{
    /**
     * @brief Throw an invalid_argument exception if vec has a length other than 1
     */
    template <typename T, int n>
    void throw_if_not_unit(const ggmath::vec::vec<T, n>& vec)
    {
        // TODO: Probably better to solve with with std::format
        if (!ggmath::vec::is_unit_vector(vec))
        {
            std::stringstream ss;

            ss << "Parameter was expected to be a unit vector"
                  "(A vector with a length of 1). "
                  "Instead, it had a length of "
               << ggmath::vec::length(vec);

            throw std::invalid_argument(ss.str());
        }
    }
}    // namespace ggmath::debug
#endif    // GG_MATH_VEC_HPP
