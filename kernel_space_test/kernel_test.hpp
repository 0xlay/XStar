#pragma once
#include <ntddk.h>

#define XSTAR_KTEST(test_suite, test_case)\
void XStar_##test_suite_##test_case()

#define XSTAR_CALL_KTEST(test_suite, test_case)\
XStar_##test_suite_##test_case()

#define XSTAR_KTEST_SUITE(test_suite)\
void XStar_Run_##test_suite()

#define XSTAR_KTEST_RUN_SUITE(test_suite)\
XStar_Run_##test_suite()

#define XSTAR_KTEST_RUN_TEST(test, method_name)\
KdPrint(("Start %s!\n", method_name));\
test;\
KdPrint(("Finish %s!\n", method_name))

//
// Assertions
//

#define XSTAR_KTEST_ASSERT_EQ(exp1, exp2)\
    NT_ASSERT(exp1 == exp2)

#define XSTAR_KTEST_ASSERT_NE(exp1, exp2)\
    NT_ASSERT(exp1 != exp2)

#define XSTAR_KTEST_ASSERT_GT(exp1, exp2)\
    NT_ASSERT(exp1 > exp2)

#define XSTAR_KTEST_ASSERT_GE(exp1, exp2)\
    NT_ASSERT(exp1 >= exp2)

#define XSTAR_KTEST_ASSERT_LT(exp1, exp2)\
    NT_ASSERT(exp1 < exp2)

#define XSTAR_KTEST_ASSERT_LE(exp1, exp2)\
    NT_ASSERT(exp1 <= exp2)

#define XSTAR_KTEST_ASSERT_TRUE(exp)\
    NT_ASSERT(exp)

#define XSTAR_KTEST_ASSERT_FALSE(exp)\
    NT_ASSERT(!exp)
