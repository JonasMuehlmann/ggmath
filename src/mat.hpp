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
