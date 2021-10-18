#include "pch.h"

TEST(WinAPIExceptionTests, WinAPIException__WithoutArguments__Test)
{
    using namespace xstar;

    auto invalidHandle = CreateFile($T"", 0, 0, nullptr, OPEN_EXISTING, 0, nullptr);

    try
    {
        throw WinAPIException();
    }
    catch (const std::exception& ex)
    {
        EXPECT_NE(ex.what(), getLastErrorStr());
    }
}

TEST(WinAPIExceptionTests, WinAPIException__WithArguments__Test)
{
    using namespace xstar;

    const char* msg = "Test error. Error code: 0x1";

    try
    {
        throw WinAPIException("Test error.", 1);
    }
    catch (const std::exception& ex)
    {
        EXPECT_EQ(ex.what(), msg);
    }
}
