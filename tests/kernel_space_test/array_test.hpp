#pragma once
#include "kernel_test.hpp"
#include "include/array.hpp"


XSTAR_KTEST(ArrayTest, Empty)
{
    xstar::Array<int, 0> arr;

    XSTAR_KTEST_ASSERT_TRUE(arr.empty());
}

XSTAR_KTEST(ArrayTest, WithPrimitiveTypes)
{
    xstar::Array<int, 3> arr = { 1, 2, 3};

    XSTAR_KTEST_ASSERT_FALSE(arr.empty());
    XSTAR_KTEST_ASSERT_EQ(arr.size(), 3);
}

XSTAR_KTEST(ArrayTest, WithAbstractTypes)
{
    class A
    {
    public:
        A(int a) : a_(a)
        { }
    private:
        int a_;
    };

    xstar::Array<A, 3> arr = { A(1), A(2), A(3) };

    XSTAR_KTEST_ASSERT_FALSE(arr.empty());
    XSTAR_KTEST_ASSERT_EQ(arr.size(), 3);
}

XSTAR_KTEST(ArrayTest, Swap)
{
    const xstar::Array<int, 3> firstSource = { 1, 2, 3 };
    const xstar::Array<int, 3> secondSource = { 4, 5, 6 };
    xstar::Array<int, 3> first = { 1, 2, 3 };
    xstar::Array<int, 3> second = { 4, 5, 6 };

    first.swap(second);

    XSTAR_KTEST_ASSERT_EQ(first, secondSource);
    XSTAR_KTEST_ASSERT_EQ(second, firstSource);
}

XSTAR_KTEST(ArrayTest, Fill)
{
    const xstar::Array<int, 3> arrSource = { 7, 7, 7 };
    xstar::Array<int, 3> arr{};
    arr.fill(7);

    XSTAR_KTEST_ASSERT_EQ(arr, arrSource);
}

XSTAR_KTEST(ArrayTest, At)
{
    xstar::Array<int, 3> arr = { 7, 8, 9 };
    arr.at(0).unwrap() = 12;
    XSTAR_KTEST_ASSERT_EQ(arr.at(0).unwrap(), 12);
}

XSTAR_KTEST(ArrayTest, ConstAt)
{
    const xstar::Array<int, 3> arr = { 7, 8, 9 };
    XSTAR_KTEST_ASSERT_EQ(arr.at(1).unwrap(), 8);
}

XSTAR_KTEST_SUITE(ArrayTest)
{
    KdPrint(("ArrayTest START!\n"));

    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ArrayTest, Empty), "ArrayTest::Empty()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ArrayTest, WithPrimitiveTypes), "ArrayTest::WithPrimitiveTypes()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ArrayTest, WithAbstractTypes), "ArrayTest::WithAbstractTypes()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ArrayTest, Swap), "ArrayTest::Swap()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ArrayTest, Fill), "ArrayTest::Fill()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ArrayTest, At), "ArrayTest::At()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ArrayTest, ConstAt), "ArrayTest::ConstAt()");

    KdPrint(("ArrayTest FINISH!\n"));
}