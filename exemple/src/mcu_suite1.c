
#define VERBOSITY_USER (0x01)

#include <mcu_suite1.h>
#include <stdio.h>

static void mcu_hello()
{
	printf("Hello world\n");
}

TEST_CASE_BEGIN(tc1)
	mcu_assert_true(1);
	mcu_assert_true(0);
	int false_toto = 0;
	mcu_assert_true(false_toto);
TEST_CASE_END()

TEST_CASE_BEGIN(tc2)
	mcu_assert_false(1);
	mcu_assert_false(0);
	int true_toto = 1;
	mcu_assert_false(true_toto);;
TEST_CASE_END()

TEST_CASE_BEGIN(tc3)
	mcu_assert(1 == 2);
	mcu_assert(1 >= 2);
	mcu_assert_message(1 == 2, "custom message");
	mcu_assert('a' >= 'b');
	mcu_assert('a' <= 'b');
TEST_CASE_END()

TEST_CASE_BEGIN(tc4)
	mcu_assert_equal_int(1,2);
TEST_CASE_END()

TEST_SUITE_BEGIN(mcu_suite1)
	TEST_CASE_RUN(tc1);
	TEST_CASE_RUN(tc2);
	TEST_CASE_RUN(tc3);
	TEST_CASE_RUN(tc4);
TEST_SUITE_END()