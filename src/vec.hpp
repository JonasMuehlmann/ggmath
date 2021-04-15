// Copyright 2021 Jonas Muehlmann
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this
// software and associated documentation files (the "Software"), to deal in the Software
// without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following
// conditions: The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED "AS
// IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
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

#include "types.hpp"
#include "util.hpp"

#ifndef GGMATH_ALLOW_SIZE_MISMATCH
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#    define GGMATH_ALLOW_SIZE_MISMATCH 0
#endif

#ifndef GGMATH_DEBUG
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#    define GGMATH_DEBUG 0
#endif


// region forward_declarations


// TODO: Check if these are really necessary
namespace ggmath::vec
{
    template <ggmath::Scalar T, int n>
    struct vec;
}    // namespace ggmath::vec


namespace ggmath::debug
{
    template <ggmath::Scalar T, int n>
    void throw_if_not_unit(const ggmath::vec::vec<T, n>& vec);

    void throw_if_not_equal_length(int n_A, int n_B);
}    // namespace ggmath::debug


// endregion forward_declarations


// region macros


// NOLINTNEXTLINE(cppcoreguidelines-macro-usage,-warnings-as-errors)
#define COMMON_MEMBERS(n)                                                                                  \
                                                                                                           \
                                                                                                           \
    /* region macros::constructors */                                                                      \
                                                                                                           \
                                                                                                           \
    constexpr explicit vec()                                                                               \
    {                                                                                                      \
        data.fill(0);                                                                                      \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    /*NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)*/     \
    constexpr explicit vec(T(&_data)[n])                                                                   \
    {                                                                                                      \
        data = std::to_array(_data);                                                                       \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    /* overload and requires clause serves as an alternative for the impossible ifdef                      \
     * inside a macro */                                                                                   \
    /* clang-format off */                                                                               \
    template <ggmath::Scalar T_In, int n_In>                                                             \
    requires (GGMATH_ALLOW_SIZE_MISMATCH == 1)                                                           \
    /*NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions) */                          \
    constexpr vec(const vec<T_In, n_In>& other)                                                          \
    {                                                                                                    \
        std::copy_n(std::begin(other), std::min(n, n_In), std::begin(data));                             \
        /* fill remaining values */                                                                      \
        std::fill_n(std::begin(data) + std::min(n, n_In), (n) - n_In , 0);                               \
    }                                                                                                    \
                                                                                                         \
    template <ggmath::Scalar T_In, int n_In>                                                             \
    requires (GGMATH_ALLOW_SIZE_MISMATCH == 0)                                                           \
    /*NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions) */                          \
    constexpr vec(const vec<T_In, n_In>& other)                                                          \
    {                                                                                                    \
        ggmath::debug::throw_if_not_equal_length(n_In, n);                                               \
        std::ranges::copy(other, std::begin(data));                                                      \
    } \
    /* clang-format on */                                                                                  \
                                                                                                           \
                                                                                                           \
    constexpr vec(const vec&& other) noexcept : data(std::move(other.data)) {}                             \
                                                                                                           \
                                                                                                           \
    constexpr vec(std::initializer_list<T> _data)                                                          \
    {                                                                                                      \
        std::ranges::copy(_data, std::begin(data));                                                        \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    /* endregion macros::cnstructors */                                                                    \
                                                                                                           \
                                                                                                           \
    /* region macros::ierators */                                                                          \
                                                                                                           \
                                                                                                           \
    constexpr auto begin() noexcept                                                                        \
    {                                                                                                      \
        return data.begin();                                                                               \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    constexpr auto begin() const noexcept                                                                  \
    {                                                                                                      \
        return data.begin();                                                                               \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    constexpr auto end() noexcept                                                                          \
    {                                                                                                      \
        return data.end();                                                                                 \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    constexpr auto end() const noexcept                                                                    \
    {                                                                                                      \
        return data.end();                                                                                 \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    constexpr auto cbegin() const noexcept                                                                 \
    {                                                                                                      \
        return data.cbegin();                                                                              \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    constexpr auto cend() const noexcept                                                                   \
    {                                                                                                      \
        return data.cend();                                                                                \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    constexpr auto rbegin() noexcept                                                                       \
    {                                                                                                      \
        return data.rbegin();                                                                              \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    constexpr auto rbegin() const noexcept                                                                 \
    {                                                                                                      \
        return data.rbegin();                                                                              \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    constexpr auto rend() noexcept                                                                         \
    {                                                                                                      \
        return data.rend();                                                                                \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    constexpr auto rend() const noexcept                                                                   \
    {                                                                                                      \
        return data.rend();                                                                                \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    constexpr auto crbegin() const noexcept                                                                \
    {                                                                                                      \
        return data.crbegin();                                                                             \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    constexpr auto crend() const noexcept                                                                  \
    {                                                                                                      \
        return data.crend();                                                                               \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    /* endregion macros::iterators */                                                                      \
                                                                                                           \
                                                                                                           \
    /* region macros::other */                                                                             \
                                                                                                           \
                                                                                                           \
    constexpr vec& operator=(const vec& other)                                                             \
    {                                                                                                      \
        if (this == &other)                                                                                \
            return *this;                                                                                  \
                                                                                                           \
        data = other;                                                                                      \
        return *this;                                                                                      \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    constexpr vec& operator=(vec&& other) noexcept                                                         \
    {                                                                                                      \
        if (this == &other)                                                                                \
            return *this;                                                                                  \
                                                                                                           \
        data = std::move(other);                                                                           \
        return *this;                                                                                      \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    constexpr T& operator[](size_t i)                                                                      \
    {                                                                                                      \
        return data[i];                                                                                    \
    }                                                                                                      \
                                                                                                           \
                                                                                                           \
    constexpr const T& operator[](size_t i) const                                                          \
    {                                                                                                      \
        return data[i];                                                                                    \
    }                                                                                                      \
                                                                                                           \
    ~vec() = default;                                                                                      \
                                                                                                           \
                                                                                                           \
    /* endregion macros::other */                                                                          \
                                                                                                           \
                                                                                                           \
    // endregion macros


namespace ggmath::vec
{
    // region classes


    template <ggmath::Scalar T, int n>
    struct vec
    {
        std::array<T, n> data;
        COMMON_MEMBERS(n)
    };


    template <ggmath::Scalar T>
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
    template <ggmath::Scalar T>
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
    template <ggmath::Scalar T>
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


    template <ggmath::Scalar T, int n>
    constexpr vec<T, n> unit_x() noexcept
    {
        vec vector = vec<T, n>();
        vector[0]  = 1;
        return vector;
    }


    template <ggmath::Scalar T, int n>
    constexpr vec<T, n> unit_y() noexcept
    {
        vec vector = vec<T, n>();
        vector[1]  = 1;
        return vector;
    }


    template <ggmath::Scalar T, int n>
    constexpr vec<T, n> unit_z() noexcept
    {
        vec vector = vec<T, n>();
        vector[2]  = 1;
        return vector;
    }


    // Allows mismatched sizes and zero-initializes missing values
    template <ggmath::Scalar T_new, ggmath::Scalar T_Other, int n_new, int n_Other>
    constexpr vec<T_new, n_new> from_other(const vec<T_Other, n_Other>& other) noexcept
    {
        vec vector = vec<T_new, n_new>();

        std::ranges::copy(other, std::begin(vector));

        return vector;
    }


    // endregion named constructors


    // region functions


    /**
     * @brief Calculate the cross product(a x b) of two vectors a and b
     */
    template <ggmath::Scalar T_A,
              ggmath::Scalar T_B,
              ggmath::Scalar T_Out = decltype(std::declval<T_A>()
                                              * std::declval<T_B>())>
    constexpr vec<T_Out, 3> cross(const vec<T_A, 3>& a, const vec<T_B, 3>& b)
    {
        return vec<T_Out, 3>(a[1] * b[2] - a[2] * b[1],
                             a[2] * b[0] - a[0] * b[2],
                             a[0] * b[1] - a[1] * b[0]);
    }


    /**
     * @brief Calculate the length of vec
     */
    template <ggmath::Scalar T, int n>
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
    template <ggmath::Scalar T, int n>
    constexpr float length_squared(const vec<T, n>& vec)
    {
        return vec * vec;
    }


    /**
     * @brief Return a copy of vec scaled to a length of 1
     */
    template <ggmath::Scalar T_In, int n>
    constexpr auto normalized(const vec<T_In, n>& vec)
    {
        return vec / length(vec);
    }


    /**
     * @brief Return a copy of vec with a length of length * factor
     */
    template <ggmath::Scalar T_In,
              ggmath::Scalar T_Factor,
              ggmath::Scalar T_Out = decltype(std::declval<T_In>()
                                              * std::declval<T_Factor>()),
              int            n>
    constexpr vec<T_Out, n> scaled_by(const vec<T_In, n>& vec, T_Factor factor)
    {
        return vec * factor;
    }

    /**
     * @brief Return a copy of vec with a length of wanted_magnitude
     */
    template <ggmath::Scalar T_In,
              ggmath::Scalar T_Magnitude,
              ggmath::Scalar T_Out = decltype(std::declval<T_In>()
                                              / std::declval<T_Magnitude>()),
              int            n>
    constexpr vec<T_Out, n> scaled_to(const vec<T_In, n>& vec,
                                      T_Magnitude         wanted_magnitude)
    {
        float factor = wanted_magnitude / length(vec);

        if (!std::isnormal(factor))
        {
            return ggmath::vec::vec<T_Out, n>();
        }
        return scaled_by(vec, factor);
    }

    /**
     * @brief Return the signed distance from a to b
     */
    template <ggmath::Scalar T_A, ggmath::Scalar T_B, int n>
    constexpr float distance(const vec<T_A, n>& a, const vec<T_B, n>& b)
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
    template <ggmath::Scalar T_A, ggmath::Scalar T_B, int n>
    constexpr bool parallel(const vec<T_A, n>& a, const vec<T_B, n>& b)
    {
#ifdef GGMATH_DEBUG
        ggmath::debug::throw_if_not_unit(a);
        ggmath::debug::throw_if_not_unit(b);
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
    template <ggmath::Scalar T_A, ggmath::Scalar T_B, int n>
    constexpr bool anti_parallel(const vec<T_A, n>& a, const vec<T_B, n>& b)
    {
#ifdef GGMATH_DEBUG
        ggmath::debug::throw_if_not_unit(a);
        ggmath::debug::throw_if_not_unit(b);
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
    template <ggmath::Scalar T_A, ggmath::Scalar T_B, int n>
    constexpr bool perpendicular(const vec<T_A, n>& a, const vec<T_B, n>& b)
    {
#ifdef GGMATH_DEBUG
        ggmath::debug::throw_if_not_unit(a);
        ggmath::debug::throw_if_not_unit(b);
#endif
        return ggmath::difference_within_epsilon(a * b, 0);
    }


    /**
     * @brief Return the angle between the vectors
     */
    template <ggmath::Scalar T_A, ggmath::Scalar T_B, int n>
    constexpr float angle_between(const vec<T_A, n>& a, const vec<T_B, n>& b)
    {
        return std::acos((a * b) / (std::abs(length(a)) * std::abs(length(b))));
    }

    /**
     * @brief Return the angle between the unit vectors*
     *
     * If the vectors have a length other than 1, the result will be incorrect.
     * Define the macro GGMATH_DEBUG to throw an exception if one of the parameters is
     * NOT a unit-vector.
     */
    template <ggmath::Scalar T_A, ggmath::Scalar T_B, int n>
    constexpr float angle_between_unit(const vec<T_A, n>& a, const vec<T_B, n>& b)
    {
#ifdef GGMATH_DEBUG
        ggmath::debug::throw_if_not_unit(a);
        ggmath::debug::throw_if_not_unit(b);
#endif
        return std::acos(a * b);
    }

    /**
     * @brief Check if the given vector has a length of 1
     */
    template <ggmath::Scalar T, int n>
    constexpr bool is_unit_vector(const vec<T, n>& vec)
    {
        return ggmath::difference_within_epsilon(length(vec), 1);
    }

    /**
     * @brief Return the smallest element in the vector
     */
    template <ggmath::Scalar T, int n>
    constexpr T min(const vec<T, n>& vec)
    {
        return *std::ranges::min_element(vec);
    }

    /**
     * @brief Return the largest element in the vector
     */
    template <ggmath::Scalar T, int n>
    constexpr T max(const vec<T, n>& vec)
    {
        return *std::ranges::max_element(vec);
    }

    /**
     * @brief Return the 0-based index of the smallest element in the vector
     */
    template <ggmath::Scalar T, int n>
    constexpr size_t index_min(const vec<T, n>& vec)
    {
        return std::ranges::distance(std::begin(vec), std::ranges::min_element(vec));
    }

    /**
     * @brief Return the 0-based index of the largest element in the vector
     */
    template <ggmath::Scalar T, int n>
    constexpr size_t index_max(const vec<T, n>& vec)
    {
        return std::ranges::distance(
            std::begin(vec), std::ranges::max_element(std::begin(vec), std::end(vec)));
    }


    /**
     * Return a vector that is the linear interpolation from a to b with a weight of t
     */
    template <ggmath::Scalar T_A,
              ggmath::Scalar T_B,
              ggmath::Scalar T_Weight,
              ggmath::Scalar T_Out = decltype(
                  std::declval<T_A>() + std::declval<T_Weight>() * std::declval<T_B>()),
              int n>
    constexpr vec<T_Out, n> lerp(const vec<T_A, n>& a, const vec<T_B, n>& b, T_Weight t)
    {
        return a + t * (b - a);
    }


    /**
     * Reflect the vector a about normal
     *
     * If the vectors have a length other than 1, the result will be incorrect.
     * Define the macro GGMATH_DEBUG to throw an exception if one of the parameters is
     * NOT a unit-vector.
     */
    template <ggmath::Scalar T_A,
              ggmath::Scalar T_B,
              ggmath::Scalar T_Out = decltype(std::declval<T_A>()
                                              * std::declval<T_B>()),
              int            n>
    constexpr vec<T_Out, n> reflect(const vec<T_A, n>& a, const vec<T_B, n>& normal)
    {
#ifdef GGMATH_DEBUG
        ggmath::debug::throw_if_not_unit(a);
        ggmath::debug::throw_if_not_unit(normal);
#endif
        return a - 2 * (a * normal) * normal;
    }


    // endregion functions


    // region operator_overloads


    // region operator_overloads::binary


    // region operator_overloads::binary::vector-vector


    // Dot product
    template <ggmath::Scalar T_A, ggmath::Scalar T_B, int n>
    constexpr float operator*(const vec<T_A, n>& a, const vec<T_B, n>& b)
    {
        return std::inner_product(std::begin(a), std::end(a), std::begin(b), 0.0);
    }


    // Cross product
    template <ggmath::Scalar T_A,
              ggmath::Scalar T_B,
              ggmath::Scalar T_Out = decltype(std::declval<T_A>()
                                              * std::declval<T_B>()),
              int            n>
    constexpr vec<T_Out, n> operator%(const vec<T_A, n>& a, const vec<T_B, n>& b)
    {
        return cross(a, b);
    }


    // Vector-vector  addition
    template <ggmath::Scalar T_A,
              ggmath::Scalar T_B,
              ggmath::Scalar T_Out = decltype(std::declval<T_A>()
                                              + std::declval<T_B>()),
              int            n>
    constexpr vec<T_Out, n> operator+(const vec<T_A, n>& a, const vec<T_B, n>& b)
    {
        auto vec_out = vec<T_Out, n>();

        std::ranges::transform(a, b, std::begin(vec_out), std::plus<>());

        return vec_out;
    }


    // Vector-vector subtraction
    template <ggmath::Scalar T_A,
              ggmath::Scalar T_B,
              ggmath::Scalar T_Out = decltype(std::declval<T_A>()
                                              - std::declval<T_B>()),
              int            n>
    constexpr vec<T_Out, n> operator-(const vec<T_A, n>& a, const vec<T_B, n>& b)
    {
        auto vec_out = vec<T_Out, n>();

        std::ranges::transform(a, b, std::begin(vec_out), std::minus<>());

        return vec_out;
    }


    // endregion operator_overloads::binary::vector-vector


    // region operator_overloads::binary::scalar-vector


    // Scalar-vector multiplication
    template <ggmath::Scalar T_Scalar,
              ggmath::Scalar T_Vec,
              ggmath::Scalar T_Out = decltype(std::declval<T_Scalar>()
                                              + std::declval<T_Vec>()),
              int            n>
    constexpr vec<T_Out, n> operator*(const T_Scalar scalar, const vec<T_Vec, n>& _vec)
    {
        auto vec_out = vec<T_Out, n>();

        std::ranges::transform(_vec, std::begin(vec_out), [scalar](T_Vec element) {
            return element * scalar;
        });

        return vec_out;
    }


    // Scalar-vector multiplication
    template <ggmath::Scalar T_Scalar,
              ggmath::Scalar T_Vec,
              ggmath::Scalar T_Out = decltype(std::declval<T_Vec>()
                                              * std::declval<T_Scalar>()),
              int            n>
    constexpr vec<T_Out, n> operator*(const vec<T_Vec, n>& vec, const T_Scalar scalar)
    {
        return scalar * vec;
    }


    // Scalar-vector division
    template <ggmath::Scalar T_Scalar,
              ggmath::Scalar T_Vec,
              ggmath::Scalar T_Out = decltype(std::declval<T_Vec>()
                                              / std::declval<T_Scalar>()),
              int            n>
    constexpr vec<T_Out, n> operator/(const vec<T_Vec, n>& vec, const T_Scalar scalar)
    {
        auto vec_out = ggmath::vec::vec<T_Out, n>();

        std::ranges::transform(vec, std::begin(vec_out), [scalar](T_Vec element) {
            return element / scalar;
        });

        return vec_out;
    }


    // endregion operator_overloads::binary::scalar-vector


    // endregion operator_overloads::binary


    // region operator_overloads::assignment


    // region operator_overloads::assignment::scalar-vector


    // Scalar-vector multiplication assignment
    template <ggmath::Scalar T_Vec, ggmath::Scalar T_Scalar, int n>
    constexpr vec<T_Vec, n>& operator*=(vec<T_Vec, n>& vec, const T_Scalar scalar)
    {
        std::ranges::transform(
            vec, std::begin(vec), [scalar](T_Vec element) { return element * scalar; });
        return vec;
    }

    // Scalar-vector division assignment
    template <ggmath::Scalar T_Vec, ggmath::Scalar T_Scalar, int n>
    constexpr vec<T_Vec, n>& operator/=(vec<T_Vec, n>& vec, const T_Scalar scalar)
    {
        std::ranges::transform(
            vec, std::begin(vec), [scalar](T_Vec element) { return element / scalar; });
        return vec;
    }


    // endregion operator_overloads::assignment::scalar-vector


    // region operator_overloads::assignment::vector-vector


    // Vector-vector addition-assignment
    template <ggmath::Scalar T_A, ggmath::Scalar T_B, int n>
    constexpr vec<T_A, n>& operator+=(vec<T_A, n>& a, const vec<T_B, n>& b)
    {
        std::ranges::transform(a, b, std::begin(a), std::plus<>());

        return a;
    }


    // Vector-vector subtraction-assignment
    template <ggmath::Scalar T_A, ggmath::Scalar T_B, int n>
    constexpr vec<T_A, n>& operator-=(vec<T_A, n>& a, const vec<T_B, n>& b)
    {
        std::ranges::transform(a, b, std::begin(a), std::minus<>());

        return a;
    }


    // endregion vector-vector


    // endregion operator_overloads::assignment


    // region operator_overloads::comparison


    // region operator_overloads::comparison::vector-vector


    // Compare component-wise equality
    template <ggmath::Scalar T_A, ggmath::Scalar T_B, int n>
    requires std::equality_comparable_with<T_A, T_B> constexpr bool operator==(
        const vec<T_A, n>& a, const vec<T_B, n>& b)
    {
        return std::ranges::equal(a, b);
    }


    // Compare component-wise equality
    template <ggmath::Scalar T_A, ggmath::Scalar T_B, int n>
    requires std::equality_comparable_with<T_A, T_B> constexpr bool operator!=(
        const vec<T_A, n>& a, const vec<T_B, n>& b)
    {
        return !std::ranges::equal(a, b);
    }


    // Compare length
    template <ggmath::Scalar T_A, ggmath::Scalar T_B, int n>
    requires std::totally_ordered_with<T_A, T_B> constexpr bool operator>(
        const vec<T_A, n>& a, const vec<T_B, n>& b)
    {
        return length(a) > length(b);
    }


    // Compare length
    template <ggmath::Scalar T_A, ggmath::Scalar T_B, int n>
    requires std::totally_ordered_with<T_A, T_B> constexpr bool operator<(
        const vec<T_A, n>& a, const vec<T_B, n>& b)
    {
        return length(a) < length(b);
    }


    // Compare length
    template <ggmath::Scalar T_A, ggmath::Scalar T_B, int n>
    requires std::totally_ordered_with<T_A, T_B> constexpr bool operator>=(
        const vec<T_A, n>& a, const vec<T_B, n>& b)
    {
        return length(a) >= length(b);
    }


    // Compare length
    template <ggmath::Scalar T_A, ggmath::Scalar T_B, int n>
    requires std::totally_ordered_with<T_A, T_B> constexpr bool operator<=(
        const vec<T_A, n>& a, const vec<T_B, n>& b)
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
        return difference_within_epsilon(length(vec), scalar);
    }


    // Compare length
    template <ggmath::Scalar T_Vec, ggmath::Scalar T_Scalar, int n>
    requires std::equality_comparable_with<T_Vec, T_Scalar> constexpr bool operator==(
        T_Scalar scalar, const vec<T_Vec, n>& vec)
    {
        return vec == scalar;
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
        return vec != scalar;
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
        return vec > scalar;
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
        return vec < scalar;
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
        return vec >= scalar;
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
        return vec <= scalar;
    }


    // endregion operator_overloads::comparison::scalar-vector


    // endregion operator_overloads::comparison


    // region operator_overloads::other


    // Invert vector
    template <ggmath::Scalar T, int n>
    constexpr vec<T, n> operator-(vec<T, n> vec)
    {
        std::ranges::transform(
            std::begin(vec), std::end(vec), std::begin(vec), std::negate<>());
        return vec;
    }


    // Format: (data[0],data[2],...,data[n])
    template <ggmath::NonCharacter T, int n>
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

    template <ggmath::Character T, int n>
    constexpr std::ostream& operator<<(std::ostream& os, const vec<T, n>& vec)
    {
        const auto last = std::end(vec) - 1;

        os << '(';
        // Loop ends before last
        // unary + prints chars as numbers
        std::for_each(
            std::begin(vec), last, [&os](T element) { os << +element << ','; });
        os << +*last;
        os << ')';

        return os;
    }


    // endregion operator_overloads::other


    // endregion operator_overloads


    using vec2f = vec<float, 2>;
    using vec3f = vec<float, 3>;
    using vec4f = vec<float, 4>;

    using vec2d = vec<double, 2>;
    using vec3d = vec<double, 3>;
    using vec4d = vec<double, 4>;

    using vec2i = vec<int, 2>;
    using vec3i = vec<int, 3>;
    using vec4i = vec<int, 4>;

    using color3 = vec<u_int8_t, 3>;
    using color4 = vec<u_int8_t, 4>;
};    // namespace ggmath::vec


namespace ggmath::debug
{
    /**
     * @brief Throw an invalid_argument exception if vec has a length other than 1
     */
    template <ggmath::Scalar T, int n>
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

    // NOLINTNEXTLINE(misc-definitions-in-headers)
    void throw_if_not_equal_length(int n_A, int n_B)
    {
        // TODO: Probably better to solve with with std::format
        if (n_A != n_B)
        {
            std::stringstream ss;

            ss << "Parameter vectors were expected to have equal lengths but they "
                  "had a length of "
               << n_A << " and " << n_B << " respectively";

            throw std::invalid_argument(ss.str());
        }
    }
}    // namespace ggmath::debug
#endif    // GG_MATH_VEC_HPP
