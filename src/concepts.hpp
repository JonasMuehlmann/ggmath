#ifndef GG_MATH_CONCEPTS_HPP
#define GG_MATH_CONCEPTS_HPP
#include <type_traits>

namespace ggmath
{
    template <typename T>
    concept Scalar = std::is_scalar<T>::value;
}    // namespace ggmath

#endif    // GG_MATH_CONCEPTS_HPP
