#include <gtest/gtest.h>

#include "util.hpp"

TEST(Util, RadToDegAny)
{
    auto result = ggmath::rad_to_deg(2.23);
    ASSERT_FLOAT_EQ(result, 127.76958);
}
TEST(Util, RadToDegMin)
{
    auto result = ggmath::rad_to_deg(0);
    ASSERT_FLOAT_EQ(result, 0);
}
TEST(Util, RadToDegMax)
{
    auto result = ggmath::rad_to_deg(2 * std::numbers::pi);
    ASSERT_FLOAT_EQ(result, 360);
}
TEST(Util, RadToDegReturnFloatFromFloat)
{
    auto result    = ggmath::rad_to_deg(1.0F);
    using is_float = std::is_same<typeof(result), float>;

    ASSERT_EQ(is_float::value, true);
}
TEST(Util, RadToDegReturnDoubleFromDouble)
{
    auto result     = ggmath::rad_to_deg(1.0);
    using is_double = std::is_same<typeof(result), double>;

    ASSERT_EQ(is_double::value, true);
}
TEST(Util, RadToDegReturnDoubleFromInt)
{
    auto result     = ggmath::rad_to_deg(1);
    using is_double = std::is_same<typeof(result), double>;

    ASSERT_EQ(is_double::value, true);
}


TEST(Util, DegToRadAny)
{
    auto result = ggmath::deg_to_rad(127.76958);
    ASSERT_FLOAT_EQ(result, 2.23);
}
TEST(Util, DegToRadMin)
{
    auto result = ggmath::deg_to_rad(0);
    ASSERT_FLOAT_EQ(result, 0);
}
TEST(Util, DegToRadMax)
{
    auto result = ggmath::deg_to_rad(360);
    ASSERT_FLOAT_EQ(result, 2 * std::numbers::pi);
}
TEST(Util, DegToRadReturnFloatFromFloat)
{
    auto result    = ggmath::deg_to_rad(1.0F);
    using is_float = std::is_same<typeof(result), float>;

    ASSERT_EQ(is_float::value, true);
}
TEST(Util, DegToRadReturnDoubleFromDouble)
{
    auto result     = ggmath::deg_to_rad(1.0);
    using is_double = std::is_same<typeof(result), double>;

    ASSERT_EQ(is_double::value, true);
}
TEST(Util, DegToRadReturnDoubleFromInt)
{
    auto result     = ggmath::deg_to_rad(1);
    using is_double = std::is_same<typeof(result), double>;

    ASSERT_EQ(is_double::value, true);
}
