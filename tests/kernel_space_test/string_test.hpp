#pragma once
#include "kernel_test.hpp"
#include "include/type_traits.hpp"
#include "include/string.hpp"


XSTAR_KTEST(StringTest, Move)
{
    xstar::ks::String<PagedPool> dest(xstar::ks::String<PagedPool>("Hello World!"));

    dest = xstar::move("My Friend");

    XSTAR_KTEST_ASSERT_EQ(dest, "My Friend");
}

XSTAR_KTEST(StringTest, Copy)
{
    xstar::ks::String<PagedPool> src("Hello World!");
    xstar::ks::String<PagedPool> dest = src;

    XSTAR_KTEST_ASSERT_EQ(src, dest);
}

XSTAR_KTEST(StringTest, Iterators)
{
    xstar::ks::String<PagedPool> src("Hello");
    XSTAR_KTEST_ASSERT_EQ(*src.begin(), 'H');
    XSTAR_KTEST_ASSERT_EQ(*(--src.end()), 'o');
}

XSTAR_KTEST(StringTest, ConstIterators)
{
    const xstar::ks::String<PagedPool> src("Hello");

    XSTAR_KTEST_ASSERT_EQ(*src.cbegin(), 'H');
    XSTAR_KTEST_ASSERT_EQ(*(--src.cend()), 'o');
}

XSTAR_KTEST(StringTest, ReverseIterators)
{
    xstar::ks::String<PagedPool> src("Hello");

    XSTAR_KTEST_ASSERT_EQ(*src.rbegin(), 'o');
    XSTAR_KTEST_ASSERT_EQ(*(--src.rend()), 'H');
}

XSTAR_KTEST(StringTest, ConstReverseIterators)
{
    const xstar::ks::String<PagedPool> src("Hello");

    XSTAR_KTEST_ASSERT_EQ(*src.crbegin(), 'o');
    XSTAR_KTEST_ASSERT_EQ(*(--src.crend()), 'H');
}

XSTAR_KTEST(StringTest, Equal)
{
    xstar::ks::String<PagedPool> src1("Hello World!");
    xstar::ks::String<PagedPool> src2("Hello World!");

    XSTAR_KTEST_ASSERT_EQ(src1, src2);
}

XSTAR_KTEST(StringTest, NotEqual)
{
    xstar::ks::String<PagedPool> src1("Hello World!");
    xstar::ks::String<PagedPool> src2("Hi World!");

    XSTAR_KTEST_ASSERT_NE(src1, src2);
}

XSTAR_KTEST(StringTest, Greater)
{
    xstar::ks::String<PagedPool> src1("Banana");
    xstar::ks::String<PagedPool> src2("Apple");

    XSTAR_KTEST_ASSERT_GT(src1, src2);
}

XSTAR_KTEST(StringTest, GreaterOrEqual)
{
    xstar::ks::String<PagedPool> src1("Banana");
    xstar::ks::String<PagedPool> src2("Apple");
    xstar::ks::String<PagedPool> src3("Apple");

    XSTAR_KTEST_ASSERT_GE(src1, src2);
    XSTAR_KTEST_ASSERT_GE(src2, src3);
}

XSTAR_KTEST(StringTest, Less)
{
    xstar::ks::String<PagedPool> src1("Apple");
    xstar::ks::String<PagedPool> src2("Banana");

    XSTAR_KTEST_ASSERT_LT(src1, src2);
}

XSTAR_KTEST(StringTest, LessOrEqual)
{
    xstar::ks::String<PagedPool> src1("Apple");
    xstar::ks::String<PagedPool> src2("Banana");
    xstar::ks::String<PagedPool> src3("Banana");

    XSTAR_KTEST_ASSERT_LE(src1, src2);
    XSTAR_KTEST_ASSERT_LE(src2, src3);
}

XSTAR_KTEST(StringTest, SquareBracket)
{
    xstar::ks::String<PagedPool> str("Hello");
    str[0] = 'h';

    XSTAR_KTEST_ASSERT_EQ(str, "hello");
}

XSTAR_KTEST(StringTest, Concatenation)
{
    xstar::ks::String<PagedPool> str("Hello, ");
    str += "0xlay!";

    XSTAR_KTEST_ASSERT_EQ(str, "Hello, 0xlay!");
}

XSTAR_KTEST_SUITE(StringTest)
{
    KdPrint(("StringTest START!\n"));

    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(StringTest, Move), "StringTest::Move()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(StringTest, Copy), "StringTest::Copy()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(StringTest, Iterators), "StringTest::Iterators()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(StringTest, ConstIterators), "StringTest::ConstIterators()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(StringTest, ReverseIterators), "StringTest::ReverseIterators()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(StringTest, ConstReverseIterators), "StringTest::ConstReverseIterators()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(StringTest, Equal), "StringTest::Equal()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(StringTest, NotEqual), "StringTest::NotEqual()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(StringTest, Greater), "StringTest::Greater()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(StringTest, GreaterOrEqual), "StringTest::GreaterOrEqual()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(StringTest, Less), "StringTest::Less()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(StringTest, LessOrEqual), "StringTest::LessOrEqual()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(StringTest, SquareBracket), "StringTest::SquareBracketl()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(StringTest, LessOrEqual), "StringTest::LessOrEqual()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(StringTest, Concatenation), "StringTest::Concatenation()");

    KdPrint(("StringTest FINISH!\n"));
}
