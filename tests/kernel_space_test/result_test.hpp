#pragma once
#include "kernel_test.hpp"
#include "include/result.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// Primitive
//
///////////////////////////////////////////////////////////////////////////////

XSTAR_KTEST(ResultTest, PrimitiveIsError)
{
    using namespace xstar::ks;

    Result<char, int> res(-1);

    XSTAR_KTEST_ASSERT_TRUE(res.isError());
    XSTAR_KTEST_ASSERT_EQ(res.isError().error, -1);
}

XSTAR_KTEST(ResultTest, PrimitiveUnwrapWithoutError)
{
    using namespace xstar::ks;

    Result<char, int> res('a');

    XSTAR_KTEST_ASSERT_FALSE(res.isError());
    XSTAR_KTEST_ASSERT_EQ(res.unwrap(), 'a');
}

XSTAR_KTEST(ResultTest, PrimitiveUnwrapWithError)
{
    using namespace xstar::ks;

    Result<char, int> res(-1);

    res.unwrap();
}

///////////////////////////////////////////////////////////////////////////////
//
// Abstract
//
///////////////////////////////////////////////////////////////////////////////

XSTAR_KTEST(ResultTest, AbstractIsError)
{
    using namespace xstar::ks;

    struct A {};
    class B
    {
    public:
        B(int b) : b_(b) {}
        int get() const { return b_; }
    private:
        int b_;
    };

    Result<A, B> res(B(-1));
    
    XSTAR_KTEST_ASSERT_TRUE(res.isError());
    XSTAR_KTEST_ASSERT_EQ(res.isError().error.get(), -1);
}

XSTAR_KTEST(ResultTest, AbstractUnwrapWithoutError)
{
    using namespace xstar::ks;

    class A
    {
    public:
        A(int a) : a_(a) {}
        int get() const { return a_; }
    private:
        int a_;
    };
    struct B {};

    Result<A, B> res(A(10));

    XSTAR_KTEST_ASSERT_FALSE(res.isError());
    XSTAR_KTEST_ASSERT_EQ(res.unwrap().get(), 10);
}

XSTAR_KTEST(ResultTest, AbstractUnwrapWithError)
{
    using namespace xstar::ks;

    struct A {};
    class B
    {
    public:
        B(int b) : b_(b) {}
        int get() const { return b_; }
    private:
        int b_;
    };

    Result<A, B> res(B(-1));

    res.unwrap();
}

///////////////////////////////////////////////////////////////////////////////
//
// XSTAR_KTEST_SUITE(ResultTest)
//
///////////////////////////////////////////////////////////////////////////////

XSTAR_KTEST_SUITE(ResultTest)
{
    KdPrint(("ResultTest START!\n"));

    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ResultTest, PrimitiveIsError), "ResultTest::PrimitiveIsError()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ResultTest, PrimitiveUnwrapWithoutError), "ResultTest::PrimitiveUnwrapWithoutError()");
    // XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ResultTest, PrimitiveUnwrapWithError), "ResulTest::PrimitiveUnwrapWithError()");

    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ResultTest, AbstractIsError), "ResultTest::AbstractIsError()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ResultTest, AbstractUnwrapWithoutError), "ResultTest::AbstractUnwrapWithoutError()");
    // XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(ResultTest, AbstractUnwrapWithError), "ResulTest::AbstractUnwrapWithError()");

    KdPrint(("ResultTest FINISH!\n"));
}
