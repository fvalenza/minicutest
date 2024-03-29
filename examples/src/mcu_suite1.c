
#define VERBOSITY_USER (0x01)

#include <mcu_suite1.h>
#include <stdio.h>




static int equal_2d_points(const point2D a, const point2D b)
{
	return ((a.a == b.a) && (a.b == b.b));
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
	mcu_assert_false(true_toto);

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



TEST_CASE_BEGIN(tc5)

	point2D pa = {1, 2};
	point2D pb = {3, 4};
	// mcu_assert_equal_custom_cmp(equal_2d_points, pa, pb);
	mcu_assert_not_equal_custom_cmp(equal_2d_points, pa, pb);

TEST_CASE_END()

TEST_CASE_BEGIN(tc6)

	float f1 = 1.3;
	float f2 = 1.4;
	float f3 = 1.401;
	mcu_assert_equal_float(f1, f2, 1e-2);
	mcu_assert_equal_float(f1, f2, 1);
	mcu_assert_equal_float(f3, f2, 1e-2);

	double d1 = 1525681.4056;
	double d2 = 1525681.4055;
	double d3 = 1525681.401;
	mcu_assert_equal_double(d1, d2, 1e-4);
	mcu_assert_equal_double(d1, d2, 1e-3);
	mcu_assert_equal_double(d3, d2, 1e-3);

TEST_CASE_END()



TEST_CASE_BEGIN(tc7)

	const char string1[10] = "Hello";
	const char string2[10] = "World";
	const char string3[10] = "World";

	mcu_assert_equal_string(string1, string2);
	mcu_assert_equal_string(string3, string2);
	mcu_assert_not_equal_string(string3, string2);

TEST_CASE_END()


TEST_CASE_BEGIN(tc8)

	int array_int1[5] = {1, 2, 3, 4, 5};
	int array_int2[5] = {2, 2, 3, 4, 5};
	int array_int3[5] = {2, 2, 3, 4, 5};

	mcu_assert_equal_int_array(array_int1, array_int2, 5);
	mcu_assert_equal_int_array(array_int3, array_int2, 5);

	point2D array_p2d_1[2] = {{1, 2},{2,3}};
	point2D array_p2d_2[2] = {{1,3},{2,3}};
	mcu_assert_equal_custom_cmp_array(equal_2d_points,array_p2d_1, array_p2d_2, 2);

TEST_CASE_END()




TEST_SUITE_BEGIN(mcu_suite1)

	test_case_run(tc1);
	test_case_run(tc2);
	test_case_run(tc3);
	test_case_run(tc4);
	test_case_run(tc5);
	test_case_run(tc7);
	test_case_run(tc8);

TEST_SUITE_END()