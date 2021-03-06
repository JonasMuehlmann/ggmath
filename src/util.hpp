// Copyright 2021-2022 Jonas Muehlmann
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
#ifndef GG_MATH_UTIL_HPP
#define GG_MATH_UTIL_HPP


#include <numbers>
#include <type_traits>

#include "types.hpp"


namespace ggmath
{
    /**
     * @brief Convert the given measure of radians to degrees
     *
     * If T is a float, the return value is a float too, otherwise it is a double
     */
    template <Scalar T>
    constexpr float_or_double<T> rad_to_deg(T radians)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
        return radians / std::numbers::pi * 180;
    }


    /**
     * @brief Convert the given measure of degrees to radians
     *
     * If T is a float, the return value is a float too, otherwise it is a double
     */
    template <Scalar T>
    constexpr float_or_double<T> deg_to_rad(T degrees)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
        return degrees * std::numbers::pi / 180;
    }


    /**
     * @brief Check if the absolute difference between the given values is less than
     * epsilon
     *
     * At least one parameter has to be a floating point value.
     */
    template <ggmath::Scalar T, ggmath::Scalar U>
    requires ggmath::any_of_concept<std::is_floating_point, T, U>
    constexpr bool difference_within_epsilon(T a, U b)
    {
        return std::abs(a - b) < std::numeric_limits<
                   typename std::conditional<ggmath::any_of_type<float, T, U>,
                                             float,
                                             double>::type>::epsilon();
    }


    /**
     * @brief Check if the absolute difference between the given values is less than
     * a specified epsilon
     *
     * At least one of a and b must be a floating point value.
     */
    template <ggmath::Scalar T, ggmath::Scalar U, std::floating_point T_Epsilon>
    requires ggmath::any_of_concept<std::is_floating_point, T, U>
    constexpr bool difference_within_epsilon(T a, U b, T_Epsilon epsilon)
    {
        return std::abs(a - b) < epsilon;
    }
}    // namespace ggmath
#endif    // GG_MATH_UTIL_HPP
