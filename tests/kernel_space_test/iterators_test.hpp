#pragma once
#include "kernel_test.hpp"
#include "include/iterators.hpp"

template <class InputIter>
const wchar_t* IteratorTestFoo(InputIter, InputIter, xstar::ks::InputIteratorTag)
{ return L"InputIterator"; }

template <class OutputIter>
const wchar_t* IteratorTestFoo(OutputIter, OutputIter, xstar::ks::OutputIteratorTag)
{ return L"OutputIterator"; }

template <class It>
const wchar_t* IteratorTestFoo(It begin, It end)
{
    return IteratorTestFoo(begin, end, typename xstar::ks::IteratorTraits<It>::IteratorCategory());
}


XSTAR_KTEST(IteratorsTest, InputIterator)
{
    int arr[] = { 1, 2, 3};
    const wchar_t* iter = IteratorTestFoo(xstar::ks::InputIterator<int>(&arr[0]), xstar::ks::InputIterator<int>(&arr[2]));
    XSTAR_KTEST_ASSERT_EQ(wcscmp(iter, L"InputIterator"), 0);
}

XSTAR_KTEST(IteratorsTest, OutputIterator)
{
    int arr[] = { 1, 2, 3 };
    const wchar_t* iter = IteratorTestFoo(xstar::ks::OutputIterator<int>(&arr[0]), xstar::ks::OutputIterator<int>(&arr[2]));
    XSTAR_KTEST_ASSERT_EQ(wcscmp(iter, L"OutputIterator"), 0);
}


XSTAR_KTEST_SUITE(IteratorsTest)
{
    KdPrint(("IteratorTests START!\n"));

    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(IteratorsTest, InputIterator), "IteratorsTest::InputIterator()");
    XSTAR_KTEST_RUN_TEST(XSTAR_CALL_KTEST(IteratorsTest, InputIterator), "IteratorsTest::OutputIterator()");

    KdPrint(("IteratorTests FINISH!\n"));
}