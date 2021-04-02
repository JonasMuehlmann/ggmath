#include <gtest/gtest.h>

#include <iostream>

#include "vec.hpp"

TEST(Vec, CrossProductAny)
{
    ggmath::vec::vec3f a             = ggmath::vec::vec3f(2, 3, 4);
    ggmath::vec::vec3f b             = ggmath::vec::vec3f(5, 6, 7);
    ggmath::vec::vec3f cross_product = a % b;

    ASSERT_EQ(cross_product, ggmath::vec::vec3f(-3, 6, -3));
}

TEST(Vec, CrossProductSelf)
{
    ggmath::vec::vec3f a             = ggmath::vec::vec3f(2, 3, 4);
    ggmath::vec::vec3f cross_product = ggmath::vec::cross(a, a);
    ggmath::vec::vec3f zero_vector   = ggmath::vec::vec3f();

    ASSERT_EQ(cross_product, zero_vector);
}

TEST(Vec, DotProductAny)
{
    ggmath::vec::vec3f a           = ggmath::vec::vec3f(2, 3, 4);
    ggmath::vec::vec3f b           = ggmath::vec::vec3f(5, 6, 7);
    float              dot_product = a * b;

    ASSERT_EQ(dot_product, 56);
}
TEST(Vec, DotProductSelf)
{
    ggmath::vec::vec3f a              = ggmath::vec::vec3f(2, 3, 4);
    float              dot_product    = a * a;
    float              length_squared = ggmath::vec::length_squared(a);

    ASSERT_EQ(dot_product, length_squared);
}
TEST(Vec, DotProductUnitParallel)
{
    ggmath::vec::vec3f a           = ggmath::vec::vec3f(1, 0, 0);
    float              dot_product = a * a;

    ASSERT_EQ(dot_product, 1);
}
TEST(Vec, DotProductUnitAntiParallel)
{
    ggmath::vec::vec3f a           = ggmath::vec::vec3f(1, 0, 0);
    ggmath::vec::vec3f b           = ggmath::vec::vec3f(-1, 0, 0);
    float              dot_product = a * b;

    ASSERT_EQ(dot_product, -1);
}
TEST(Vec, DotProductUnitPerpendicular)
{
    ggmath::vec::vec3f a           = ggmath::vec::vec3f(1, 0, 0);
    ggmath::vec::vec3f b           = ggmath::vec::vec3f(0, 1, 0);
    float              dot_product = a * b;

    ASSERT_EQ(dot_product, 0);
}
