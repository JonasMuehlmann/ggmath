#include <gtest/gtest.h>

#include <numbers>

#include "vec.hpp"

using namespace ggmath;


// region functions


TEST(Vec, LengthAny)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_FLOAT_EQ(vector::length(a), 5.3851647);
}
TEST(Vec, LengthZero)
{
    vec3f zero_vector = vec3f();

    ASSERT_EQ(vector::length(zero_vector), 0);
}
TEST(Vec, LengthNegative)
{
    vec3f zero_vector = vec3f(-2, -3, -4);

    ASSERT_FLOAT_EQ(vector::length(zero_vector), 5.3851647);
}


TEST(Vec, LengthSquaredAny)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_EQ(vector::length_squared(a), 29);
}
TEST(Vec, LengthSquaredZero)
{
    vec3f zero_vector = vec3f();

    ASSERT_EQ(vector::length_squared(zero_vector), 0);
}
TEST(Vec, LengthSquaredNegative)
{
    vec3f a = vec3f(-2, -3, -4);

    ASSERT_EQ(vector::length_squared(a), 29);
}


TEST(Vec, NormalizedAny)
{
    vec3f a          = vec3f(2, 3, 4);
    vec3f normalized = vector::normalized(a);

    ASSERT_FLOAT_EQ(vector::length(normalized), 1);
}
TEST(Vec, NormalizedZero)
{
    vec3f a          = vec3f(0, 0, 0);
    vec3f normalized = vector::normalized(a);

    ASSERT_EQ(isnanf(vector::length(normalized)), true);
}
TEST(Vec, NormalizedNegative)
{
    vec3f a          = vec3f(-2, -3, -4);
    vec3f normalized = vector::normalized(a);

    ASSERT_FLOAT_EQ(vector::length(normalized), 1);
}


TEST(Vec, ScaledByAny)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vector::scaled_by(a, 2);

    ASSERT_FLOAT_EQ(vector::length(b), 10.770329);
}
TEST(Vec, ScaledByZeroFactor)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vector::scaled_by(a, 0);

    ASSERT_FLOAT_EQ(vector::length(b), 0);
}
TEST(Vec, ScaledByZeroVector)
{
    vec3f a = vec3f(0, 0, 0);
    vec3f b = vector::scaled_by(a, 2);

    ASSERT_FLOAT_EQ(vector::length(b), 0);
}


TEST(Vec, ScaledToAny)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vector::scaled_to(a, 2);

    ASSERT_FLOAT_EQ(vector::length(b), 2);
}
TEST(Vec, ScaledToZeroScalar)
{
    vec3f a = vec3f();
    vec3f b = vector::scaled_to(a, 0);

    ASSERT_FLOAT_EQ(vector::length(b), 0);
}
TEST(Vec, ScaledToZeroVector)
{
    vec3f a = vec3f();
    vec3f b = vector::scaled_to(a, 2);

    ASSERT_FLOAT_EQ(vector::length(b), 0);
}


TEST(Vec, DistanceAny)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(5, 6, 7);

    ASSERT_FLOAT_EQ(vector::distance(a, b), 5.196152);
}
TEST(Vec, DistanceCompareWithReversed)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(5, 6, 7);

    ASSERT_FLOAT_EQ(vector::distance(b, a), vector::distance(a, b));
}
TEST(Vec, DistanceSelf)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_FLOAT_EQ(vector::distance(a, a), 0);
}
TEST(Vec, DistanceFromOrigin)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_FLOAT_EQ(vector::distance(vec3f(), a), vector::length(a));
}


TEST(Vec, ParallelAny)
{
    vec3f a           = vector::normalized(vec3f(2, 3, 4));
    vec3f b           = vector::normalized(vec3f(4, 6, 8));
    bool  is_parallel = vector::parallel(a, b);

    ASSERT_EQ(is_parallel, true);
}
TEST(Vec, ParallelAnyNot)
{
    vec3f a           = vector::normalized(vec3f(2, 3, 4));
    vec3f b           = vector::normalized(vec3f(4, 6, 7));
    bool  is_parallel = vector::parallel(a, b);

    ASSERT_EQ(is_parallel, false);
}
TEST(Vec, ParallelZero)
{
    vec3f a           = vector::normalized(vec3f(2, 3, 4));
    vec3f zero_vector = vec3f();

#ifdef GGMATH_DEBUG
    ASSERT_THROW(vector::parallel(a, zero_vector), std::invalid_argument);
#else
    bool is_parallel = vector::parallel(a, zero_vector);
    ASSERT_EQ(is_parallel, false);
#endif
}


TEST(Vec, AntiParallelAny)
{
    vec3f a                = vector::normalized(vec3f(2, 3, 4));
    vec3f b                = vector::normalized(vec3f(-4, -6, -8));
    bool  is_anti_parallel = vector::anti_parallel(a, b);

    ASSERT_EQ(is_anti_parallel, true);
}
TEST(Vec, AntiParallelAnyNot)
{
    vec3f a                = vector::normalized(vec3f(2, 3, 4));
    vec3f b                = vector::normalized(vec3f(4, 6, 7));
    bool  is_anti_parallel = vector::anti_parallel(a, b);

    ASSERT_EQ(is_anti_parallel, false);
}
TEST(Vec, AntiParallelZero)
{
    vec3f a           = vector::normalized(vec3f(2, 3, 4));
    vec3f zero_vector = vec3f();

#ifdef GGMATH_DEBUG
    ASSERT_THROW(vector::anti_parallel(a, zero_vector), std::invalid_argument);
#else
    bool is_anti_parallel = vector::anti_parallel(a, zero_vector);
    ASSERT_EQ(is_anti_parallel, false);
#endif
}


TEST(Vec, PerpendicularAny)
{
    vec3f a                = vector::normalized(vec3f(1, -2, 3));
    vec3f b                = vector::normalized(vec3f(5, 4, 1));
    bool  is_perpendicular = vector::perpendicular(a, b);
    ASSERT_EQ(is_perpendicular, true);
}
TEST(Vec, PerpendicularAnyNot)
{
    vec3f a                = vector::normalized(vec3f(2, 3, 4));
    vec3f b                = vector::normalized(vec3f(5, 6, 7));
    bool  is_perpendicular = vector::perpendicular(a, b);

    ASSERT_EQ(is_perpendicular, false);
}
TEST(Vec, PerpendicularZero)
{
    vec3f a           = vector::normalized(vec3f(2, 3, 4));
    vec3f zero_vector = vec3f();

#ifdef GGMATH_DEBUG
    ASSERT_THROW(vector::perpendicular(a, zero_vector), std::invalid_argument);
#else
    bool is_perpendicular = vector::perpendicular(a, zero_vector);
    ASSERT_EQ(is_perpendicular, true);
#endif
}


TEST(Vec, AngleBetweenAny)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(4, 3, 2);

    ASSERT_FLOAT_EQ(vector::angle_between(a, b), 0.531458);
}
TEST(Vec, AngleBetweenPerpendicular)
{
    vec3f a = vector::normalized(vec3f(1, -2, 3));
    vec3f b = vector::normalized(vec3f(5, 4, 1));


    ASSERT_FLOAT_EQ(vector::angle_between(a, b), 1.5707963);
}
TEST(Vec, AngleBetweenParallel)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(4, 6, 8);

    ASSERT_FLOAT_EQ(vector::angle_between(a, b), 0);
}
TEST(Vec, AngleBetweenAntiParallel)
{
    vec3f a = vector::normalized(vec3f(2, 3, 4));
    vec3f b = vector::normalized(vec3f(-4, -6, -8));

    ASSERT_FLOAT_EQ(vector::angle_between(a, b), std::numbers::pi);
}


TEST(Vec, AngleBetweenUnitAny)
{
    vec3f a = vector::normalized(vec3f(2, 3, 4));
    vec3f b = vector::normalized(vec3f(4, 3, 2));

    ASSERT_FLOAT_EQ(vector::angle_between_unit(a, b), 0.531458);
}
TEST(Vec, AngleBetweenUnitPerpendicular)
{
    vec3f a = vector::normalized(vec3f(1, -2, 3));
    vec3f b = vector::normalized(vec3f(5, 4, 1));

    ASSERT_FLOAT_EQ(vector::angle_between_unit(a, b), 1.5707963);
}
TEST(Vec, AngleBetweenUnitParallel)
{
    vec3f a = vector::normalized(vec3f(2, 3, 4));
    vec3f b = vector::normalized(vec3f(4, 6, 8));

    ASSERT_FLOAT_EQ(vector::angle_between_unit(a, b), 0);
}
TEST(Vec, AngleBetweenUnitAntiParallel)
{
    vec3f a = vector::normalized(vec3f(2, 3, 4));
    vec3f b = vector::normalized(vec3f(-4, -6, -8));

    ASSERT_FLOAT_EQ(vector::angle_between_unit(a, b), std::numbers::pi);
}
#ifdef GGMATH_DEBUG
TEST(Vec, AngleBetweenUnitNotUnit)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(-4, -6, -8);

    ASSERT_THROW(vector::angle_between_unit(a, b), std::invalid_argument);
}
#endif


TEST(Vec, IsUnitVectorAny)
{
    vec3f a = vector::normalized(vec3f(2, 3, 4));
    ASSERT_EQ(vector::is_unit_vector(a), true);
}
TEST(Vec, IsUnitVectorAnyNot)
{
    vec3f a = vec3f(2, 3, 4);
    ASSERT_EQ(vector::is_unit_vector(a), false);
}
TEST(Vec, IsUnitVectorZero)
{
    vec3f a = vector::normalized(vec3f());
    ASSERT_EQ(vector::is_unit_vector(a), false);
}


TEST(Vec, MinAny)
{
    vec3f a = vec3f(4, 3, 2);

    ASSERT_EQ(vector::min(a), 2);
}


TEST(Vec, MaxAny)
{
    vec3f a = vec3f(4, 3, 2);

    ASSERT_EQ(vector::max(a), 4);
}


TEST(Vec, IndexMinAny)
{
    vec3f a = vec3f(4, 3, 2);

    ASSERT_EQ(vector::index_min(a), 2);
}


TEST(Vec, IndexMaxAny)
{
    vec3f a = vec3f(4, 3, 2);

    ASSERT_EQ(vector::index_max(a), 0);
}


TEST(Vec, LerpAny)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 6, 10);

    vec3f c = vector::lerp(a, b, 0.3);

    ASSERT_EQ(c, vec3f(2, 3.9, 5.8));
}
TEST(Vec, LerpTZero)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 6, 10);

    vec3f c = vector::lerp(a, b, 0);

    ASSERT_EQ(c, a);
}
TEST(Vec, LerpTOne)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 6, 10);

    vec3f c = vector::lerp(a, b, 1);

    ASSERT_EQ(c, b);
}
TEST(Vec, LerpTZeroFromZero)
{
    vec3f a = vec3f();
    vec3f b = vec3f(2, 6, 10);

    vec3f c = vector::lerp(a, b, 0);

    ASSERT_EQ(c, a);
}
TEST(Vec, LerpTOneFromZero)
{
    vec3f a = vec3f();
    vec3f b = vec3f(2, 6, 10);

    vec3f c = vector::lerp(a, b, 1);

    ASSERT_EQ(c, b);
}


TEST(Vec, ReflectAny)
{
    vec3f a      = vector::normalized(vec3f(1, 1, 0));
    vec3f normal = vec3f(-1, 0, 0);

    vec3f b = vector::reflect(a, normal);
    ASSERT_EQ(b, vector::normalized(vec3f(-1, 1, 0)));
}
TEST(Vec, ReflectPerpendicular)
{
    vec3f a      = vec3f(0, 0, 1);
    vec3f normal = vec3f(-1, 0, 0);
    vec3f b      = vector::reflect(a, normal);

    ASSERT_EQ(b, a);
}
TEST(Vec, ReflectAntiParallel)
{
    vec3f a      = vec3f(1, 0, 0);
    vec3f normal = vec3f(-1, 0, 0);
    vec3f b      = vector::reflect(a, normal);

    ASSERT_EQ(b, vec3f(-1, 0, 0));
}
TEST(Vec, ReflectParallel)
{
    vec3f a      = vector::normalized(vec3f(2, 3, 4));
    vec3f normal = vec3f(-1, 0, 0);
    vec3f b      = vector::reflect(a, normal);

    ASSERT_EQ(b, b);
}


// endregion functions


// region operator overloads


// region binary operators


// region vector-vector


TEST(Vec, CrossProductAny)
{
    vec3f a             = vec3f(2, 3, 4);
    vec3f b             = vec3f(5, 6, 7);
    vec3f cross_product = a % b;

    ASSERT_EQ(cross_product, vec3f(-3, 6, -3));
}
TEST(Vec, CrossProductSelf)
{
    vec3f a = vec3f(2, 3, 4);
    // NOLINTNEXTLINE(misc-redundant-expression)
    vec3f cross_product = a % a;
    vec3f zero_vector   = vec3f();

    ASSERT_EQ(cross_product, zero_vector);
}


TEST(Vec, DotProductAny)
{
    vec3f a           = vec3f(2, 3, 4);
    vec3f b           = vec3f(5, 6, 7);
    float dot_product = a * b;

    ASSERT_EQ(dot_product, 56);
}
TEST(Vec, DotProductSelf)
{
    vec3f a              = vec3f(2, 3, 4);
    float dot_product    = a * a;
    float length_squared = vector::length_squared(a);

    ASSERT_EQ(dot_product, length_squared);
}
TEST(Vec, DotProductUnitParallel)
{
    vec3f a           = vec3f(1, 0, 0);
    float dot_product = a * a;

    ASSERT_EQ(dot_product, 1);
}
TEST(Vec, DotProductUnitAntiParallel)
{
    vec3f a           = vec3f(1, 0, 0);
    vec3f b           = vec3f(-1, 0, 0);
    float dot_product = a * b;

    ASSERT_EQ(dot_product, -1);
}
TEST(Vec, DotProductUnitPerpendicular)
{
    vec3f a           = vec3f(1, 0, 0);
    vec3f b           = vec3f(0, 1, 0);
    float dot_product = a * b;

    ASSERT_EQ(dot_product, 0);
}


TEST(Vec, Addition)
{
    vec3f a = vec3f(1, 0, 0);
    vec3f b = vec3f(0, 1, 0);
    vec3f c = a + b;

    ASSERT_EQ(c, vec3f(1, 1, 0));
}
TEST(Vec, AdditionWithNegativeComponends)
{
    vec3f a = vec3f(-1, 0, 0);
    vec3f b = vec3f(0, 1, 0);
    vec3f c = a + b;

    ASSERT_EQ(c, vec3f(-1, 1, 0));
}
TEST(Vec, Subtraction)
{
    vec3f a = vec3f(1, 1, 0);
    vec3f b = vec3f(0, 1, 0);
    vec3f c = a - b;

    ASSERT_EQ(c, vec3f(1, 0, 0));
}
TEST(Vec, SubtractionWithNegativeComponends)
{
    vec3f a = vec3f(-1, -1, 0);
    vec3f b = vec3f(0, 1, 0);
    vec3f c = a - b;

    ASSERT_EQ(c, vec3f(-1, -2, 0));
}


// endregion vector-vector


// region scalar-vector


TEST(Vec, MultiplicationAny)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = a * 5;

    ASSERT_EQ(b, vec3f(10, 15, 20));
}
TEST(Vec, MultiplicationZeroFactor)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = a * 0;

    ASSERT_EQ(b, vec3f());
}
TEST(Vec, MultiplicationZeroVector)
{
    vec3f zero_vector = vec3f();
    vec3f b           = zero_vector * 5;

    ASSERT_EQ(b, vec3f());
}


TEST(Vec, DivisionAny)
{
    vec3f a = vec3f(10, 15, 20);
    vec3f b = a / 5;

    ASSERT_EQ(b, vec3f(2, 3, 4));
}
TEST(Vec, DivisionZeroFactor)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = a / 0;

    ASSERT_EQ(b, vec3f(std::numeric_limits<float>::infinity()));
}
TEST(Vec, DivisionZeroVector)
{
    vec3f zero_vector = vec3f();
    vec3f b           = zero_vector / 5;

    ASSERT_EQ(b, vec3f());
}


// endregion scalar-vector


// endregion binary operators


// region assignment operators


// region scalar-vector


TEST(Vec, MultiplicationAssignmentAny)
{
    vec3f a = vec3f(2, 3, 4);
    a *= 5;

    ASSERT_EQ(a, vec3f(10, 15, 20));
}
TEST(Vec, MultiplicationAssignmentZeroFactor)
{
    vec3f a = vec3f(2, 3, 4);
    a *= 0;

    ASSERT_EQ(a, vec3f());
}
TEST(Vec, MultiplicationAssignmentZeroVector)
{
    vec3f zero_vector = vec3f();
    zero_vector *= 5;

    ASSERT_EQ(zero_vector, vec3f());
}


TEST(Vec, DivisionAssignmentAny)
{
    vec3f a = vec3f(10, 15, 20);
    a /= 5;

    ASSERT_EQ(a, vec3f(2, 3, 4));
}
TEST(Vec, DivisionAssignmentZeroFactor)
{
    vec3f a = vec3f(2, 3, 4);
    a /= 0;

    ASSERT_EQ(a, vec3f(std::numeric_limits<float>::infinity()));
}
TEST(Vec, DivisionAssignmentZeroVector)
{
    vec3f zero_vector = vec3f();
    zero_vector /= 5;

    ASSERT_EQ(zero_vector, vec3f());
}


// endregion scalar-vector


// region vector-vector


TEST(Vec, AdditionAssignment)
{
    vec3f a = vec3f(1, 0, 0);
    vec3f b = vec3f(0, 1, 0);
    a += b;

    ASSERT_EQ(a, vec3f(1, 1, 0));
}
TEST(Vec, AdditionAssignmentWithNegativeComponends)
{
    vec3f a = vec3f(-1, 0, 0);
    vec3f b = vec3f(0, 1, 0);

    a += b;
    ASSERT_EQ(a, vec3f(-1, 1, 0));
}
TEST(Vec, SubtractionAssignment)
{
    vec3f a = vec3f(1, 1, 0);
    vec3f b = vec3f(0, 1, 0);
    a -= b;
    ASSERT_EQ(a, vec3f(1, 0, 0));
}
TEST(Vec, SubtractionAssignmentWithNegativeComponends)
{
    vec3f a = vec3f(-1, -1, 0);
    vec3f b = vec3f(0, 1, 0);

    a -= b;
    ASSERT_EQ(a, vec3f(-1, -2, 0));
}


// endregion vector-vector


// endregion assignment operators


// region comparison operators


// region vector-vector


TEST(Vec, EqualAny)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_EQ(a == a, true);
}
TEST(Vec, EqualAnyNot)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 3, 3);

    ASSERT_EQ(a == b, false);
}


TEST(Vec, UnequalAny)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 3, 3);

    ASSERT_EQ(a != b, true);
}
TEST(Vec, UnequalAnyNot)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_EQ(a != a, false);
}


TEST(Vec, LongerAny)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 3, 3);

    ASSERT_EQ(a > b, true);
}
TEST(Vec, LongerAnyNot)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 3, 3);

    ASSERT_EQ(b > a, false);
}


TEST(Vec, ShorterAny)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 3, 3);

    ASSERT_EQ(b < a, true);
}
TEST(Vec, ShorterAnyNot)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 3, 3);

    ASSERT_EQ(a < b, false);
}


TEST(Vec, LongerOrEqualAny)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 3, 3);

    ASSERT_EQ(a >= b, true);
}
TEST(Vec, LongerOrEqualAnyNot)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 3, 3);

    ASSERT_EQ(b >= a, false);
}
TEST(Vec, LongerOrEqualAnyEqual)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 3, 4);

    ASSERT_EQ(a >= b, true);
}


TEST(Vec, ShorterOrEqualAny)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 3, 3);

    ASSERT_EQ(b <= a, true);
}
TEST(Vec, ShorterOrEqualAnyNot)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 3, 3);

    ASSERT_EQ(a <= b, false);
}
TEST(Vec, ShorterOrEqualAnyEqual)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 3, 4);

    ASSERT_EQ(b <= a, true);
}


// endregion vector-vector


// region scalar-vector


TEST(Vec, LengthEqualAny)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_EQ(a == vector::length(a), true);
}
TEST(Vec, LengthEqualAnyNot)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 3, 3);

    ASSERT_EQ(a == vector::length(b), false);
}


TEST(Vec, LengthUnequalAny)
{
    vec3f a = vec3f(2, 3, 4);
    vec3f b = vec3f(2, 3, 3);

    ASSERT_EQ(a != vector::length(b), true);
}
TEST(Vec, LengthUnequalAnyNot)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_EQ(a != vector::length(a), false);
}


TEST(Vec, LengthLongerAny)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_EQ(a > 2, true);
}
TEST(Vec, LengthLongerAnyNot)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_EQ(a > 6, false);
}


TEST(Vec, LengthShorterAny)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_EQ(a < 6, true);
}
TEST(Vec, LengthShorterAnyNot)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_EQ(a < 5, false);
}


TEST(Vec, LengthLongerOrEqualAny)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_EQ(a >= 5, true);
}
TEST(Vec, LengthLongerOrEqualAnyNot)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_EQ(6 >= a, false);
}
TEST(Vec, LengthLongerOrEqualAnyEqual)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_EQ(a >= vector::length(a), true);
}


TEST(Vec, LengthShorterOrEqualAny)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_EQ(6 <= a, true);
}
TEST(Vec, LengthShorterOrEqualAnyNot)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_EQ(a <= 4, false);
}
TEST(Vec, LengthShorterOrEqualAnyEqual)
{
    vec3f a = vec3f(2, 3, 4);

    ASSERT_EQ(vector::length(a) <= a, true);
}


// endregion scalar-vector


// endregion comparison operators


// endregion operator overloads