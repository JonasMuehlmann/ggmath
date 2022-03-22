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
#ifndef GG_MATH_TYPES_HPP
#define GG_MATH_TYPES_HPP
#include <type_traits>

namespace ggmath
{
    /**
     * Check if at least one of the listed types satisfies the given concept(first
     * parameter)
     *
     * At least 1 type has to be passed after the concept.
     */
    template <template <typename> class Concept, typename... Types>
    concept any_of_concept = requires(Types...)
    {
        sizeof...(Types) > 0;
        (... || Concept<Types>::value);
    };


    /**
     * Check if all of the given types support the concept(first parameter)
     *
     * At least 1 type has to be passed after the concept.
     */
    template <template <typename> class Concept, typename... Types>
    concept all_of_concept = requires(Types...)
    {
        sizeof...(Types) > 0;
        (... || Concept<Types>::value);
    };


    /**
     * Check if at least one of the listed types is equal to the first one
     *
     * At least two types have to be passed.
     */
    template <typename T, typename... Types>
    concept any_of_type = requires(Types...)
    {
        sizeof...(Types) > 0;
        (... || std::is_same<T, Types>::value);
    };


    /**
     * Check if all of the listed types are equal
     *
     * At least two types have to be passed.
     */
    template <typename T, typename... Types>
    concept all_of_type = requires(Types...)
    {
        sizeof...(Types) > 0;
        (... && std::is_same<T, Types>::value);
    };


    template <typename T>
    using float_or_double =
        typename std::conditional<std::is_same<T, float>::value, float, double>::type;


    template <typename T>
    concept Scalar = std::is_scalar<T>::value;

    template <typename T>
    concept Character = ggmath::
        any_of_type<T, char, unsigned char, char8_t, char16_t, char32_t, wchar_t>;

    template <typename T>
    concept NonCharacter = !Character<T>;
}    // namespace ggmath

#endif    // GG_MATH_TYPES_HPP
