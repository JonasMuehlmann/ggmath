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
#ifndef MATH_LIB_MAT_HPP
#define MATH_LIB_MAT_HPP

template <typename T, int n, int m>
struct mat
{
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)
    T data[n][m];
    // region constructors
    constexpr explicit mat(T values);
    constexpr mat();
    // endregion constructors
    // region static methods
    // endregion static methods
    // region operator overloads
    // endregion operator overloads
    // region methods
    // endregion methods
};

template <typename T>
struct mat<T, 3, 3>
{
    // region constructors
    // endregion constructors
    // region static methods
    // endregion static methods
    // region operator overloads
    // endregion operator overloads
    // region methods
    // endregion methods
};
template <typename T>
struct mat<T, 4, 4>
{
    // region constructors
    // endregion constructors
    // region static methods
    // endregion static methods
    // region operator overloads
    // endregion operator overloads
    // region methods
    // endregion methods
};

using mat33f = mat<float, 3, 3>;
using mat44f = mat<float, 4, 4>;
#endif    // MATH_LIB_MAT_HPP
