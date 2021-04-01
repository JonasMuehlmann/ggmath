#include <gtest/gtest.h>

#include <iostream>

#include "vec.hpp"

TEST(Vec, VecCrossProduct)
{
    ggmath::vec::vec3f a             = ggmath::vec::vec3f(2, 3, 4);
    ggmath::vec::vec3f b             = ggmath::vec::vec3f(5, 6, 7);
    ggmath::vec::vec3f cross_product = ggmath::vec::cross(a, b);

    ASSERT_EQ(cross_product, ggmath::vec::vec3f(-3, 6, -3));
}
