#include <gtest/gtest.h>

#include <numbers>

#include "vec.hpp"
using namespace ggmath;


// region functions


TEST(Vec, LengthAny)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);

    ASSERT_FLOAT_EQ(vec::length(a), 5.3851647);
}
TEST(Vec, LengthZero)
{
    vec::vec3f zero_vector = vec::vec3f();

    ASSERT_EQ(vec::length(zero_vector), 0);
}
TEST(Vec, LengthNegative)
{
    vec::vec3f zero_vector = vec::vec3f(-2, -3, -4);

    ASSERT_FLOAT_EQ(vec::length(zero_vector), 5.3851647);
}


TEST(Vec, LengthSquaredAny)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);

    ASSERT_EQ(vec::length_squared(a), 29);
}
TEST(Vec, LengthSquaredZero)
{
    vec::vec3f zero_vector = vec::vec3f();

    ASSERT_EQ(vec::length_squared(zero_vector), 0);
}
TEST(Vec, LengthSquaredNegative)
{
    vec::vec3f a = vec::vec3f(-2, -3, -4);

    ASSERT_EQ(vec::length_squared(a), 29);
}


TEST(Vec, NormalizedAny)
{
    vec::vec3f a          = vec::vec3f(2, 3, 4);
    vec::vec3f normalized = vec::normalized(a);

    ASSERT_FLOAT_EQ(length(normalized), 1);
}
TEST(Vec, NormalizedZero)
{
    vec::vec3f a          = vec::vec3f(0, 0, 0);
    vec::vec3f normalized = vec::normalized(a);

    ASSERT_EQ(isnanf(length(normalized)), true);
}
TEST(Vec, NormalizedNegative)
{
    vec::vec3f a          = vec::vec3f(-2, -3, -4);
    vec::vec3f normalized = vec::normalized(a);

    ASSERT_FLOAT_EQ(length(normalized), 1);
}


TEST(Vec, ScaledByAny)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::scaled_by(a, 2);

    ASSERT_FLOAT_EQ(vec::length(b), 10.770329);
}
TEST(Vec, ScaledByZeroFactor)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::scaled_by(a, 0);

    ASSERT_FLOAT_EQ(vec::length(b), 0);
}
TEST(Vec, ScaledByZeroVector)
{
    vec::vec3f a = vec::vec3f(0, 0, 0);
    vec::vec3f b = vec::scaled_by(a, 2);

    ASSERT_FLOAT_EQ(vec::length(b), 0);
}


TEST(Vec, ScaledToAny)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::scaled_to(a, 2);

    ASSERT_FLOAT_EQ(vec::length(b), 2);
}
TEST(Vec, ScaledToZeroScalar)
{
    vec::vec3f a = vec::vec3f();
    vec::vec3f b = vec::scaled_to(a, 0);

    ASSERT_FLOAT_EQ(vec::length(b), 0);
}
TEST(Vec, ScaledToZeroVector)
{
    vec::vec3f a = vec::vec3f();
    vec::vec3f b = vec::scaled_to(a, 2);

    ASSERT_FLOAT_EQ(vec::length(b), 0);
}


TEST(Vec, DistanceAny)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(5, 6, 7);

    ASSERT_FLOAT_EQ(vec::distance(a, b), 5.196152);
}
TEST(Vec, DistanceCompareWithReversed)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(5, 6, 7);

    ASSERT_FLOAT_EQ(vec::distance(b, a), vec::distance(a, b));
}
TEST(Vec, DistanceSelf)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);

    ASSERT_FLOAT_EQ(vec::distance(a, a), 0);
}
TEST(Vec, DistanceFromOrigin)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);

    ASSERT_FLOAT_EQ(vec::distance(vec::vec3f(), a), vec::length(a));
}


TEST(Vec, ParallelAny)
{
    vec::vec3f a           = vec::normalized(vec::vec3f(2, 3, 4));
    vec::vec3f b           = vec::normalized(vec::vec3f(4, 6, 8));
    bool       is_parallel = vec::parallel(a, b);

    ASSERT_EQ(is_parallel, true);
}
TEST(Vec, ParallelAnyNot)
{
    vec::vec3f a           = vec::normalized(vec::vec3f(2, 3, 4));
    vec::vec3f b           = vec::normalized(vec::vec3f(4, 6, 7));
    bool       is_parallel = vec::parallel(a, b);

    ASSERT_EQ(is_parallel, false);
}
TEST(Vec, ParallelZero)
{
    vec::vec3f a           = vec::normalized(vec::vec3f(2, 3, 4));
    vec::vec3f zero_vector = vec::vec3f();
    bool       is_parallel = vec::anti_parallel(a, zero_vector);

    ASSERT_EQ(is_parallel, false);
}


TEST(Vec, AntiParallelAny)
{
    vec::vec3f a           = vec::normalized(vec::vec3f(2, 3, 4));
    vec::vec3f b           = vec::normalized(vec::vec3f(-4, -6, -8));
    bool       is_parallel = vec::anti_parallel(a, b);

    ASSERT_EQ(is_parallel, true);
}
TEST(Vec, AntiParallelAnyNot)
{
    vec::vec3f a           = vec::normalized(vec::vec3f(2, 3, 4));
    vec::vec3f b           = vec::normalized(vec::vec3f(4, 6, 7));
    bool       is_parallel = vec::anti_parallel(a, b);

    ASSERT_EQ(is_parallel, false);
}
TEST(Vec, AntiParallelZero)
{
    vec::vec3f a           = vec::normalized(vec::vec3f(2, 3, 4));
    vec::vec3f zero_vector = vec::vec3f();
    bool       is_parallel = vec::parallel(a, zero_vector);

    ASSERT_EQ(is_parallel, false);
}


TEST(Vec, PerpendicularAny)
{
    vec::vec3f a                = vec::normalized(vec::vec3f(1, -2, 3));
    vec::vec3f b                = vec::normalized(vec::vec3f(5, 4, 1));
    bool       is_perpendicular = vec::perpendicular(a, b);

    ASSERT_EQ(is_perpendicular, true);
}
TEST(Vec, PerpendicularAnyNot)
{
    vec::vec3f a                = vec::normalized(vec::vec3f(2, 3, 4));
    vec::vec3f b                = vec::normalized(vec::vec3f(5, 6, 7));
    bool       is_perpendicular = vec::perpendicular(a, b);

    ASSERT_EQ(is_perpendicular, false);
}
TEST(Vec, PerpendicularZero)
{
    vec::vec3f a                = vec::normalized(vec::vec3f(2, 3, 4));
    vec::vec3f zero_vector      = vec::vec3f();
    bool       is_perpendicular = vec::perpendicular(a, zero_vector);

    ASSERT_EQ(is_perpendicular, true);
}


TEST(Vec, AngleBetweenAny)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(4, 3, 2);

    ASSERT_FLOAT_EQ(vec::angle_between(a, b), 0.531458);
}
TEST(Vec, AngleBetweenPerpendicular)
{
    vec::vec3f a = vec::normalized(vec::vec3f(1, -2, 3));
    vec::vec3f b = vec::normalized(vec::vec3f(5, 4, 1));


    ASSERT_FLOAT_EQ(vec::angle_between(a, b), 1.5707963);
}
TEST(Vec, AngleBetweenParallel)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(4, 6, 8);

    ASSERT_FLOAT_EQ(vec::angle_between(a, b), 0);
}
TEST(Vec, AngleBetweenAntiParallel)
{
    vec::vec3f a = vec::normalized(vec::vec3f(2, 3, 4));
    vec::vec3f b = vec::normalized(vec::vec3f(-4, -6, -8));

    ASSERT_FLOAT_EQ(vec::angle_between(a, b), std::numbers::pi);
}


TEST(Vec, IsUnitVectorAny)
{
    vec::vec3f a = vec::normalized(vec::vec3f(2, 3, 4));
    ASSERT_EQ(vec::is_unit_vector(a), true);
}
TEST(Vec, IsUnitVectorAnyNot)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    ASSERT_EQ(vec::is_unit_vector(a), false);
}
TEST(Vec, IsUnitVectorZero)
{
    vec::vec3f a = vec::normalized(vec::vec3f());
    ASSERT_EQ(vec::is_unit_vector(a), false);
}


TEST(Vec, MinAny)
{
    vec::vec3f a = vec::vec3f(4, 3, 2);

    ASSERT_EQ(vec::min(a), 2);
}


TEST(Vec, MaxAny)
{
    vec::vec3f a = vec::vec3f(4, 3, 2);

    ASSERT_EQ(vec::max(a), 4);
}


TEST(Vec, IndexMinAny)
{
    vec::vec3f a = vec::vec3f(4, 3, 2);

    ASSERT_EQ(vec::index_min(a), 2);
}


TEST(Vec, IndexMaxAny)
{
    vec::vec3f a = vec::vec3f(4, 3, 2);

    ASSERT_EQ(vec::index_max(a), 0);
}


TEST(Vec, LerpAny)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(2, 6, 10);

    vec::vec3f c = vec::lerp(a, b, 0.3);

    ASSERT_EQ(c, vec::vec3f(2, 3.9, 5.8));
}
TEST(Vec, LerpTZero)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(2, 6, 10);

    vec::vec3f c = vec::lerp(a, b, 0);

    ASSERT_EQ(c, a);
}
TEST(Vec, LerpTOne)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(2, 6, 10);

    vec::vec3f c = vec::lerp(a, b, 1);

    ASSERT_EQ(c, b);
}
TEST(Vec, LerpTZeroFromZero)
{
    vec::vec3f a = vec::vec3f();
    vec::vec3f b = vec::vec3f(2, 6, 10);

    vec::vec3f c = vec::lerp(a, b, 0);

    ASSERT_EQ(c, a);
}
TEST(Vec, LerpTOneFromZero)
{
    vec::vec3f a = vec::vec3f();
    vec::vec3f b = vec::vec3f(2, 6, 10);

    vec::vec3f c = vec::lerp(a, b, 1);

    ASSERT_EQ(c, b);
}

TEST(Vec, ReflectAny)
{
    vec::vec3f a      = vec::normalized(vec::vec3f(1, 1, 0));
    vec::vec3f normal = vec::vec3f(-1, 0, 0);
    vec::vec3f b      = vec::reflect(a, normal);

    ASSERT_EQ(b, vec::normalized(vec::vec3f(-1, 1, 0)));
}
TEST(Vec, ReflectPerpendicular)
{
    vec::vec3f a      = vec::vec3f(0, 0, 1);
    vec::vec3f normal = vec::vec3f(-1, 0, 0);
    vec::vec3f b      = vec::reflect(a, normal);

    ASSERT_EQ(b, a);
}
TEST(Vec, ReflectAntiParallel)
{
    vec::vec3f a      = vec::vec3f(1, 0, 0);
    vec::vec3f normal = vec::vec3f(-1, 0, 0);
    vec::vec3f b      = vec::reflect(a, normal);

    ASSERT_EQ(b, vec::vec3f(-1, 0, 0));
}
TEST(Vec, ReflectParallel)
{
    vec::vec3f a      = vec::normalized(vec::vec3f(2, 3, 4));
    vec::vec3f normal = vec::vec3f(-1, 0, 0);
    vec::vec3f b      = vec::reflect(a, normal);

    ASSERT_EQ(b, b);
}
// endregion functions


// region operator overloads


// region binary operators


// region vector-vector


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

TEST(Vec, Addition)
{
    vec::vec3f a = vec::vec3f(1, 0, 0);
    vec::vec3f b = vec::vec3f(0, 1, 0);
    vec::vec3f c = a + b;

    ASSERT_EQ(c, vec::vec3f(1, 1, 0));
}
TEST(Vec, AdditionWithNegativeComponends)
{
    vec::vec3f a = vec::vec3f(-1, 0, 0);
    vec::vec3f b = vec::vec3f(0, 1, 0);
    vec::vec3f c = a + b;

    ASSERT_EQ(c, vec::vec3f(-1, 1, 0));
}
TEST(Vec, Subtraction)
{
    vec::vec3f a = vec::vec3f(1, 1, 0);
    vec::vec3f b = vec::vec3f(0, 1, 0);
    vec::vec3f c = a - b;

    ASSERT_EQ(c, vec::vec3f(1, 0, 0));
}
TEST(Vec, SubtractionWithNegativeComponends)
{
    vec::vec3f a = vec::vec3f(-1, -1, 0);
    vec::vec3f b = vec::vec3f(0, 1, 0);
    vec::vec3f c = a - b;

    ASSERT_EQ(c, vec::vec3f(-1, -2, 0));
}


// endregion vector-vector


// region scalar-vector


TEST(Vec, MultiplicationAny)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = a * 5;

    ASSERT_EQ(b, vec::vec3f(10, 15, 20));
}
TEST(Vec, MultiplicationZeroFactor)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = a * 0;

    ASSERT_EQ(b, vec::vec3f());
}
TEST(Vec, MultiplicationZeroVector)
{
    vec::vec3f zero_vector = vec::vec3f();
    vec::vec3f b           = zero_vector * 5;

    ASSERT_EQ(b, vec::vec3f());
}


TEST(Vec, DivisionAny)
{
    vec::vec3f a = vec::vec3f(10, 15, 20);
    vec::vec3f b = a / 5;

    ASSERT_EQ(b, vec::vec3f(2, 3, 4));
}
TEST(Vec, DivisionZeroFactor)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = a / 0;

    ASSERT_EQ(b, vec::vec3f(std::numeric_limits<float>::infinity()));
}
TEST(Vec, DivisionZeroVector)
{
    vec::vec3f zero_vector = vec::vec3f();
    vec::vec3f b           = zero_vector / 5;

    ASSERT_EQ(b, vec::vec3f());
}


// endregion scalar-vector


// endregion binary operators


// region assignment operators


// region scalar-vector


TEST(Vec, MultiplicationAssignmentAny)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    a *= 5;

    ASSERT_EQ(a, vec::vec3f(10, 15, 20));
}
TEST(Vec, MultiplicationAssignmentZeroFactor)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    a *= 0;

    ASSERT_EQ(a, vec::vec3f());
}
TEST(Vec, MultiplicationAssignmentZeroVector)
{
    vec::vec3f zero_vector = vec::vec3f();
    zero_vector *= 5;

    ASSERT_EQ(zero_vector, vec::vec3f());
}


TEST(Vec, DivisionAssignmentAny)
{
    vec::vec3f a = vec::vec3f(10, 15, 20);
    a /= 5;

    ASSERT_EQ(a, vec::vec3f(2, 3, 4));
}
TEST(Vec, DivisionAssignmentZeroFactor)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    a /= 0;

    ASSERT_EQ(a, vec::vec3f(std::numeric_limits<float>::infinity()));
}
TEST(Vec, DivisionAssignmentZeroVector)
{
    vec::vec3f zero_vector = vec::vec3f();
    zero_vector /= 5;

    ASSERT_EQ(zero_vector, vec::vec3f());
}


// endregion scalar-vector


// region vector-vector


TEST(Vec, AdditionAssignment)
{
    vec::vec3f a = vec::vec3f(1, 0, 0);
    vec::vec3f b = vec::vec3f(0, 1, 0);
    a += b;

    ASSERT_EQ(a, vec::vec3f(1, 1, 0));
}
TEST(Vec, AdditionAssignmentWithNegativeComponends)
{
    vec::vec3f a = vec::vec3f(-1, 0, 0);
    vec::vec3f b = vec::vec3f(0, 1, 0);

    a += b;
    ASSERT_EQ(a, vec::vec3f(-1, 1, 0));
}
TEST(Vec, SubtractionAssignment)
{
    vec::vec3f a = vec::vec3f(1, 1, 0);
    vec::vec3f b = vec::vec3f(0, 1, 0);
    a -= b;
    ASSERT_EQ(a, vec::vec3f(1, 0, 0));
}
TEST(Vec, SubtractionAssignmentWithNegativeComponends)
{
    vec::vec3f a = vec::vec3f(-1, -1, 0);
    vec::vec3f b = vec::vec3f(0, 1, 0);

    a -= b;
    ASSERT_EQ(a, vec::vec3f(-1, -2, 0));
}

// endregion vector-vector


// endregion assignment operators


// region comparison operators


// region vector-vector


TEST(Vec, EqualAny)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);

    ASSERT_EQ(a == a, true);
}
TEST(Vec, EqualAnyNot)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(2, 3, 3);

    ASSERT_EQ(a == b, false);
}


TEST(Vec, UnequalAny)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(2, 3, 3);

    ASSERT_EQ(a != b, true);
}
TEST(Vec, UnequalAnyNot)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);

    ASSERT_EQ(a != a, false);
}


TEST(Vec, LongerAny)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(2, 3, 3);

    ASSERT_EQ(a > b, true);
}
TEST(Vec, LongerAnyNot)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(2, 3, 3);

    ASSERT_EQ(b > a, false);
}


TEST(Vec, ShorterAny)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(2, 3, 3);

    ASSERT_EQ(b < a, true);
}
TEST(Vec, ShorterAnyNot)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(2, 3, 3);

    ASSERT_EQ(a < b, false);
}


TEST(Vec, LongerOrEqualAny)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(2, 3, 3);

    ASSERT_EQ(a >= b, true);
}
TEST(Vec, LongerOrEqualAnyNot)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(2, 3, 3);

    ASSERT_EQ(b >= a, false);
}
TEST(Vec, LongerOrEqualAnyEqual)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(2, 3, 4);

    ASSERT_EQ(a >= b, true);
}


TEST(Vec, ShorterOrEqualAny)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(2, 3, 3);

    ASSERT_EQ(b <= a, true);
}
TEST(Vec, ShorterOrEqualAnyNot)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(2, 3, 3);

    ASSERT_EQ(a <= b, false);
}
TEST(Vec, ShorterOrEqualAnyEqual)
{
    vec::vec3f a = vec::vec3f(2, 3, 4);
    vec::vec3f b = vec::vec3f(2, 3, 4);

    ASSERT_EQ(b <= a, true);
}
// endregion vector-vector


// region scalar-vector


// endregion scalar-vector


// endregion comparison operators


// endregion operator overloads