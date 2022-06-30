#pragma once
#include "kernel_test.hpp"
#include "include/array.hpp"


XSTAR_KTEST(ArrayTest, Empty)
{
    using namespace xstar::ks;
    Array<int, 0> arr;

    XSTAR_KTEST_ASSERT_TRUE(arr.empty());
}

XSTAR_KTEST(ArrayTest, WithPrimitiveTypes)
{
    using namespace xstar::ks;
    Array<int, 3> arr = { 1, 2, 3};

    XSTAR_KTEST_ASSERT_FALSE(arr.empty());
    XSTAR_KTEST_ASSERT_EQ(arr.size(), 3);
}

XSTAR_KTEST(ArrayTest, WithAbstractTypes)
{
    using namespace xstar::ks;

    class A
    {
    public:
        A(int a) : a_(a)
        { }
    private:
        int a_;
    };

    Array<A, 3> arr = {A(1), A(2), A(3)};

    XSTAR_KTEST_ASSERT_FALSE(arr.empty());
    XSTAR_KTEST_ASSERT_EQ(arr.size(), 3);
}

XSTAR_KTEST(ArrayTest, Swap)
{
    using namespace xstar::ks;

    const Array<int, 3> firstSource = { 1, 2, 3 };
    const Array<int, 3> secondSource = { 4, 5, 6 };
    Array<int, 3> first = { 1, 2, 3 };
    Array<int, 3> second = { 4, 5, 6 };

    first.swap(second);

    XSTAR_KTEST_ASSERT_EQ(first, secondSource);
    XSTAR_KTEST_ASSERT_EQ(second, firstSource);
}

XSTAR_KTEST(ArrayTest, Fill)
{
    using namespace xstar::ks;

    const Array<int, 3> arrSource = {7, 7, 7};
    Array<int, 3> arr{};

    arr.fill(7);

    XSTAR_KTEST_ASSERT_EQ(arr, arrSource);
}

XSTAR_KTEST(ArrayTest, At)
{
    using namespace xstar::ks;

    Array<int, 3> arr = { 7, 8, 9 };

    arr.at(0).unwrap() = 12;

    XSTAR_KTEST_ASSERT_EQ(arr.at(0).unwrap(), 12);
}

XSTAR_KTEST(ArrayTest, ConstAt)
{
    using namespace xstar::ks;

    const Array<int, 3> arr = { 7, 8, 9 };

    XSTAR_KTEST_ASSERT_EQ(arr.at(1).unwrap(), 8);
}

//
// Iterators
//

XSTAR_KTEST(ArrayTest, ConstIterator)
{
    using namespace xstar::ks;

    const Array<int, 3> arr = { 7, 8, 9 };

    XSTAR_KTEST_ASSERT_EQ(*(arr.cbegin()), 7);
    XSTAR_KTEST_ASSERT_EQ(*(--arr.cend()), 9);
}

XSTAR_KTEST(ArrayTest, Iterator)
{
    using namespace xstar::ks;

    Array<int, 3> arr = { 7, 8, 9 };

    XSTAR_KTEST_ASSERT_EQ(*(arr.begin()), 7);
    XSTAR_KTEST_ASSERT_EQ(*(--arr.end()), 9);
}


XSTAR_KTEST(ArrayTest, ConstReverseIterator)
{
    using namespace xstar::ks;

    const Array<int, 3> arr = { 7, 8, 9 };

    XSTAR_KTEST_ASSERT_EQ(*(arr.crbegin()), 9);
    XSTAR_KTEST_ASSERT_EQ(*(--arr.crend()), 7);
}

XSTAR_KTEST(ArrayTest, ReverseIterator)
{
    using namespace xstar::ks;

    Array<int, 3> arr = { 7, 8, 9 };

    XSTAR_KTEST_ASSERT_EQ(*(arr.rbegin()), 9);
    XSTAR_KTEST_ASSERT_EQ(*(--arr.rend()), 7);
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
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ArrayTest, ConstIterator), "ArrayTest::ConstIterator()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ArrayTest, Iterator), "ArrayTest::Iterator()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ArrayTest, ConstReverseIterator), "ArrayTest::ConstReverseIterator()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ArrayTest, ReverseIterator), "ArrayTest::ReverseIterator()");

    KdPrint(("ArrayTest FINISH!\n"));
}
