#pragma once
#include "kernel_test.hpp"
#include "result.hpp"


XSTAR_KTEST(ResultTest, IsError)
{
    xstar::Result<char, int> res;

    res.error(-1);

    XSTAR_KTEST_ASSERT_TRUE(res.isError());
}

XSTAR_KTEST(ResultTest, UnwrapWithoutError)
{
    xstar::Result<char, int> res;

    res.some('a');

    XSTAR_KTEST_ASSERT_EQ(res.unwrap(), 'a');
}

XSTAR_KTEST(ResultTest, UnwrapWithError)
{
    xstar::Result<char, int> res;

    res.error(-1);

    res.unwrap();
}

XSTAR_KTEST_SUITE(ResultTest)
{
    KdPrint(("StringTest START!\n"));

    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ResultTest, IsError), "ResultTest::IsError()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ResultTest, UnwrapWithoutError), "ResultTest::UnwrapWithoutError()");
    // XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ResultTest, UnwrapWithError), "ResulTest::UnwrapWithError()");

    KdPrint(("StringTest FINISH!\n"));
}
