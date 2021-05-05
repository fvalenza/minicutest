
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
	mcu_assert_not_equal_int(2,2);
	mcu_assert_equal_char('a','b');
	mcu_assert_equal_char('a','b');
	int toto1, toto2;
	int* ptoto1 = &toto1;
	int* ptoto2 = &toto2; 
	mcu_assert_equal_ptr(ptoto1, ptoto2);
	mcu_assert_null_ptr(ptoto1);
	ptoto1 = NULL;
	mcu_assert_null_ptr(ptoto1);

TEST_CASE_END()

typedef struct
{
	int a;
	int b;
} point2D;

int equal_2d_points(const point2D a, const point2D b)
{
	return ((a.a == b.a) && (a.b == b.b));
}

TEST_CASE_BEGIN(tc5)
	point2D pa = {1, 2};
	point2D pb = {3, 4};
	mcu_assert_equal_custom_cmp(equal_2d_points, pa, pb);
TEST_CASE_END()


TEST_SUITE_BEGIN(mcu_suite1)
	TEST_CASE_RUN(tc1);
	TEST_CASE_RUN(tc2);
	TEST_CASE_RUN(tc3);
	TEST_CASE_RUN(tc4);
	TEST_CASE_RUN(tc5);
TEST_SUITE_END()