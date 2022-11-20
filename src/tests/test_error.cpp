#include "error.h"
#include <gtest/gtest.h>

TEST(TestError, ErrorClass)
{
    {
        static constexpr core::Error err{"Test"};
        ASSERT_STREQ(err.msg, "Test");
        ASSERT_EQ(err.type, core::Error::TYPE::UNKNOW);
    }
    {
        static constexpr auto error_type = core::Error::TYPE::OUT_OF_MEMORY;
        static constexpr core::Error err{"Test", error_type};
        ASSERT_STREQ(err.msg, "Test");
        ASSERT_EQ(err.type, error_type);
    }
}

TEST(TestReturn, ReturnConstruction)
{
    {
        static constexpr auto ref = 123;
        static constexpr core::ReturnValue<int> v{ref};
        ASSERT_TRUE(v.isValue());
        ASSERT_TRUE(v);
        ASSERT_TRUE(v.isSuccess());
        ASSERT_FALSE(v.isError());

        ASSERT_EQ(v.getValue(), ref);

        ASSERT_EQ(static_cast<int>(v), ref);
        ASSERT_EQ(v.cast<float>().getValue(), float(ref));
        ASSERT_EQ(core::cast_to_success(v), core::SUCCESS);

        ASSERT_EQ(v.getError().type, core::Error::TYPE::INVALID_ERROR_REQUEST);
    }

    {
        static constexpr auto error_type = core::Error::TYPE::OUT_OF_BOUNDS;

        static constexpr auto err = core::Error{"Error", error_type};

        static const core::ReturnValue<int> v{err};
        ASSERT_FALSE(v.isValue());
        ASSERT_FALSE(v);
        ASSERT_FALSE(v.isSuccess());
        ASSERT_TRUE(v.isError());

        ASSERT_TRUE(v.cast<float>().isError());
        ASSERT_TRUE(core::cast_to_success(v).isError());

        ASSERT_EQ(v.getError().type, error_type);
        ASSERT_STREQ(v.getError().msg, "Error");
    }
}

namespace
{
core::ReturnVoid get_success()
{
    return core::SUCCESS;
}

core::ReturnVoid get_error()
{
    return core::Error{"Error", core::Error::TYPE::INVALID_STATE};
}

core::ReturnValue<int> get_int()
{
    return 99;
}

core::ReturnValue<int> get_int_error()
{
    return core::Error{"Error", core::Error::TYPE::OUT_OF_BOUNDS};
}

template <typename T> core::ReturnValue<float> get_float(T f)
{
    return f().cast<float>();
}

core::ReturnValue<int> return_error(bool err)
{
    if (err)
        return core::Error{"Error"};
    return 123;
}

core::ReturnValue<int> pass() {
    return get_int();
}

} // namespace

TEST(TestReturn, ReturnUsage)
{
    {
        const auto res = get_success();
        ASSERT_TRUE(res.isSuccess());
    }
    {
        const auto res = get_error();
        ASSERT_TRUE(res.isError());
    }
    {
        const auto res = get_float(get_int);
        ASSERT_TRUE(res.isValue());
    }
    {
        const auto res = get_float(get_int_error);
        ASSERT_TRUE(res.isError());
    }
    {
        const auto res = return_error(false);
        ASSERT_TRUE(res.isSuccess());
    }
    {
        const auto res = return_error(true);
        ASSERT_TRUE(res.isError());
    }
    {
        const auto res = pass();
        ASSERT_TRUE(res.isValue());
    }
}
