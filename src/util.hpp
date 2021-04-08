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
}    // namespace ggmath
#endif    // GG_MATH_UTIL_HPP
