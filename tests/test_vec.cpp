#include <gtest/gtest.h>

#include <iostream>

#include "vec.hpp"
using namespace ggmath;
// region functions
TEST(Vec, LengthAny)
{
    vec::vec3f a      = vec::vec3f(2, 3, 4);
    float      length = vec::length(a);

    ASSERT_FLOAT_EQ(length, 5.3851647);
}
TEST(Vec, LengthZero)
{
    vec::vec3f zero_vector = vec::vec3f();
    float      length      = vec::length(zero_vector);

    ASSERT_EQ(length, 0);
}

TEST(Vec, LengthSquaredAny)
{
    vec::vec3f a      = vec::vec3f(2, 3, 4);
    float      length = vec::length_squared(a);

    ASSERT_EQ(length, 29);
}
TEST(Vec, LengthSquaredZero)
{
    vec::vec3f zero_vector = vec::vec3f();
    float      length      = vec::length_squared(zero_vector);

    ASSERT_EQ(length, 0);
}
// endregion functions
// region operator overloads
TEST(Vec, CrossProductAny)
{
    vec::vec3f a             = vec::vec3f(2, 3, 4);
    vec::vec3f b             = vec::vec3f(5, 6, 7);
    vec::vec3f cross_product = a % b;

    ASSERT_EQ(cross_product, vec::vec3f(-3, 6, -3));
}
TEST(Vec, CrossProductSelf)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    // NOLINTNEXTLINE(misc-redundant-expression)
    vec::vec3f cross_product = a % a;
    vec::vec3f zero_vector   = vec::vec3f();

    ASSERT_EQ(cross_product, zero_vector);
}

TEST(Vec, DotProductAny)
{
    vec::vec3f a           = vec::vec3f(2, 3, 4);
    vec::vec3f b           = vec::vec3f(5, 6, 7);
    float      dot_product = a * b;

    ASSERT_EQ(dot_product, 56);
}
TEST(Vec, DotProductSelf)
{
    vec::vec3f a              = vec::vec3f(2, 3, 4);
    float      dot_product    = a * a;
    float      length_squared = vec::length_squared(a);

    ASSERT_EQ(dot_product, length_squared);
}
TEST(Vec, DotProductUnitParallel)
{
    vec::vec3f a           = vec::vec3f(1, 0, 0);
    float      dot_product = a * a;

    ASSERT_EQ(dot_product, 1);
}
TEST(Vec, DotProductUnitAntiParallel)
{
    vec::vec3f a           = vec::vec3f(1, 0, 0);
    vec::vec3f b           = vec::vec3f(-1, 0, 0);
    float      dot_product = a * b;

    ASSERT_EQ(dot_product, -1);
}
TEST(Vec, DotProductUnitPerpendicular)
{
    vec::vec3f a           = vec::vec3f(1, 0, 0);
    vec::vec3f b           = vec::vec3f(0, 1, 0);
    float      dot_product = a * b;

    ASSERT_EQ(dot_product, 0);
}

TEST(Vec, Add)
{
    vec::vec3f a = vec::vec3f(1, 0, 0);
    vec::vec3f b = vec::vec3f(0, 1, 0);
    vec::vec3f c = a + b;

    ASSERT_EQ(c, vec::vec3f(1, 1, 0));
}
TEST(Vec, AddWithNegativeComponends)
{
    vec::vec3f a = vec::vec3f(-1, 0, 0);
    vec::vec3f b = vec::vec3f(0, 1, 0);
    vec::vec3f c = a + b;

    ASSERT_EQ(c, vec::vec3f(-1, 1, 0));
}
// endregion operator overloads
