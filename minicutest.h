/*  MINCUTEST  - MINImalist C UnitTEST framework
*
* Copyright © 2021 florian[dot]valenza[at]gmail[dot]com
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#ifndef __MINICUTEST_H__
#define __MINICUTEST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// For usage of do{} while(0) with NO semicolon at the end of the macro (hence user shall put semicolon after each macro call)
// see http://c-faq.com/cpp/multistmt.html

// for print formating : https://fr.wikipedia.org/wiki/Types_de_donn%C3%A9e_du_langage_C


#ifndef CUSTOM_PRINT_METHOD
#define LOG_FUNCTION printf
#else
#define LOG_FUNCTION CUSTOM_PRINT_METHOD
#endif

#ifndef VERBOSITY_USER
#define VERBOSITY_USER (0x0)
#endif

#define VERBOSITY ( (VERBOSITY_USER & 0x01) )  // TODO :  multiple levels of verbosity ??

//TODO : is it portable ? dependencies to gcc string.h. does this work with pike for example?
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)


///
/// \brief Array of char to store log report of TEST_GROUP
///
static char group_report[500000]; // should be long enough to hold full report


///
/// \brief Basic print/log function.
///         Builds the message with useful information of where the assert has failed and call LOG_FUNCTION
///         One shall not use this MACRO. Internlly called by other macros
///
/// \param[in] filename Name of the file where this macro is called
/// \param[in] test_suite Name of the test_suite where this macro is called
/// \param[in] test_case Name of the test_case where this macro is called
/// \param[in] line Line of the source file where this macro is called
/// \param[in] message The message to print
///
#define MCU_LOG_BASE(filename, test_suite, test_case, line, message) \
    LOG_FUNCTION("%s::%s::%s:%u - Assertion failed : %s \n", filename, test_suite, test_case, line, message);


///
/// \brief Check within a test_case of a test_suite if the expression is true (C-like trueness)
///         One shall not use this MACRO. Internally called by other assert macros
///
/// \param[in] test_suite The name of the test_suite where the check is done
/// \param[in] test_case The name of the test_case where the check is done
/// \param[in] expr The expression to be tested for trueness
/// \param[in] message The message to print in case of failed test
///
#define MCU_ASSERT_BASE(test_suite, test_case, expr, message)                            \
    do {                                                              \
        *nb_tests+=1;                                                 \
        if ( !(expr) ) {                                \
            *nb_failed+=1;                                              \
            MCU_LOG_BASE(__FILENAME__, test_suite, test_case, __LINE__, message);  \
        }                                                             \
    } while (0)



#define mcu_log(message) \
    LOG_FUNCTION("%s\n", message)

#define mcu_assert_true(expr) \
    MCU_ASSERT_BASE(test_suite, __func__, (expr), "\""#expr" is not true\"")


#define mcu_assert_false(expr) \
    MCU_ASSERT_BASE(test_suite, __func__, !(expr), "\""#expr" is true\"")

#define mcu_assert(expr) \
    mcu_assert_true(expr)

#define mcu_assert_message(expr, message) \
    MCU_ASSERT_BASE(test_suite, __func__, (expr), message)




///
/// \brief Print the expected and obtained values based on printf formatting
///
/// \param[in] type The formatting type of the variables to print
/// \param[in] data Variable obtained in the assert test
/// \param[in] expected Variable expected for the assert test
///
#define MCU_LOG_VALUES(type, data, expected) \
    do { \
        if (VERBOSITY) \
        { \
            LOG_FUNCTION("Expected "#type" , obtained "#type"\n", expected, data); \
        } \
    } while (0)



#define MCU_ASSERT_EQUAL_BASE(test_suite, test_case, data, expected, message)                            \
    do { \
        MCU_ASSERT_BASE(test_suite, test_case, (data == expected), message); \
    } while (0)

#define MCU_ASSERT_NOT_EQUAL_BASE(test_suite, test_case, data, expected, message)                            \
    do { \
        MCU_ASSERT_BASE(test_suite, test_case, (!(data == expected)), message); \
    } while (0)


#define MCU_ASSERT_EQUAL_BASE_TYPE(TYPE, data, expected)                            \
    do { \
        size_t nb_failed_before = *nb_failed; \
        MCU_ASSERT_EQUAL_BASE(test_suite, __func__, data, expected, "\""#data" == "#expected"\""); \
        if (*nb_failed - nb_failed_before == 1) \
        { \
            MCU_LOG_VALUES_##TYPE(data, expected); \
        } \
    } while (0)


#define MCU_ASSERT_NOT_EQUAL_BASE_TYPE(TYPE, data, expected)                            \
    do { \
        size_t nb_failed_before = *nb_failed; \
        MCU_ASSERT_NOT_EQUAL_BASE(test_suite, __func__, data, expected, "\""#data" != "#expected"\""); \
        if (*nb_failed - nb_failed_before == 1) \
        { \
            MCU_LOG_VALUES_##TYPE(data, expected); \
        } \
    } while (0)


#define MCU_ASSERT_EQUAL_FLOATING_BASE(test_suite, test_case, float_diff, precision, message)                            \
    do { \
        MCU_ASSERT_BASE(test_suite, test_case, (float_diff <= precision), message); \
    } while (0)

#define MCU_ASSERT_NOT_EQUAL_FLOATING_BASE(test_suite, test_case, float_diff, precision, message)                            \
    do { \
        MCU_ASSERT_BASE(test_suite, test_case, (float_diff > precision), message); \
    } while (0)


#define MCU_LOG_VALUES_FLOAT(data, expected) \
    MCU_LOG_VALUES(%f, data, expected);

#define MCU_LOG_VALUES_DOUBLE(data, expected) \
    MCU_LOG_VALUES(%lf, data, expected);


#define MCU_ASSERT_EQUAL_FLOAT(data, expected, precision) \
    do { \
        const float float_diff = ((data - expected) < 0) ? -(data - expected) : (data - expected); \
        size_t nb_failed_before = *nb_failed; \
        MCU_ASSERT_EQUAL_FLOATING_BASE(test_suite, __func__, float_diff, precision, "\""#data" == "#expected"\""); \
        if (*nb_failed - nb_failed_before == 1) \
        { \
            MCU_LOG_VALUES_FLOAT(data, expected); \
        } \
    } while (0)

#define MCU_ASSERT_NOT_EQUAL_FLOAT(data, expected, precision) \
    do { \
        const float float_diff = ((data - expected) < 0) ? -(data - expected) : (data - expected); \
        size_t nb_failed_before = *nb_failed; \
        MCU_ASSERT_NOT_EQUAL_FLOATING_BASE(test_suite, __func__, float_diff, precision, "\""#data" == "#expected"\""); \
        if (*nb_failed - nb_failed_before == 1) \
        { \
            MCU_LOG_VALUES_FLOAT(data, expected); \
        } \
    } while (0)

#define MCU_ASSERT_EQUAL_DOUBLE(data, expected, precision) \
    do { \
        const double double_diff = ((data - expected) < 0) ? -(data - expected) : (data - expected); \
        size_t nb_failed_before = *nb_failed; \
        MCU_ASSERT_EQUAL_FLOATING_BASE(test_suite, __func__, double_diff, precision, "\""#data" != "#expected"\""); \
        if (*nb_failed - nb_failed_before == 1) \
        { \
            MCU_LOG_VALUES_DOUBLE(data, expected); \
        } \
    } while (0)

#define MCU_ASSERT_NOT_EQUAL_DOUBLE(data, expected, precision) \
    do { \
        const double double_diff = ((data - expected) < 0) ? -(data - expected) : (data - expected); \
        size_t nb_failed_before = *nb_failed; \
        MCU_ASSERT_NOT_EQUAL_FLOATING_BASE(test_suite, __func__, double_diff, precision, "\""#data" != "#expected"\""); \
        if (*nb_failed - nb_failed_before == 1) \
        { \
            MCU_LOG_VALUES_DOUBLE(data, expected); \
        } \
    } while (0)


#define mcu_assert_equal_float(data, expected, precision) \
    MCU_ASSERT_EQUAL_FLOAT(data, expected, precision)

// expects the relative_precision expressed in %
#define mcu_assert_equal_float_rel(data, expected, rel_precision) \
    MCU_ASSERT_EQUAL_FLOAT(data, expected, (rel_precision * expected))


#define mcu_assert_equal_double(data, expected, precision) \
    MCU_ASSERT_EQUAL_DOUBLE(data, expected, precision)

// expects the relative_precision expressed in %
#define mcu_assert_equal_double_rel(data, expected, rel_precision) \
    MCU_ASSERT_EQUAL_DOUBLE(data, expected, (rel_precision * expected))

///
/// \brief Check if two variables are "equal" ( based on custom comparison function)
///         Shall be used inside a TEST_CASE. Abstraction of BASE macro
///
/// \param[in] cmp_function Hookup function which does the comparison of data and expected variables
/// \param[in] data The first variable for comparison
/// \param[in] expected The second variable for comparison
///
#define mcu_assert_equal_custom_cmp(cmp_function, data, expected) \
    MCU_ASSERT_BASE(test_suite, __func__, ((cmp_function)((data), (expected))), "\""#data" == "#expected"\"")


///
/// \brief Check if two variables are "equal" ( based on custom comparison function)
///         Print custom message if assert fails
///         Shall be used inside a TEST_CASE. Abstraction of BASE macro
///
/// \param[in] cmp_function Hookup function which does the comparison of data and expected variables
/// \param[in] data The first variable for comparison
/// \param[in] expected The second variable for comparison
/// \param[in] message The message to print in case of failed test
///
#define mcu_assert_equal_custom_cmp_messagae(cmp_function, data, expected, message) \
    MCU_ASSERT_BASE(test_suite, __func__, ((cmp_function)((data), (expected))), message)




///
/// \brief Print the compared int variables by assert_equal_int
///
/// \param[in] data Int variable obtained in the assert test
/// \param[in] expected Int variable expected for the assert test
///
#define MCU_LOG_VALUES_CHAR(data, expected) \
    MCU_LOG_VALUES(%c, data, expected);

#define mcu_assert_equal_char(data, expected) \
    MCU_ASSERT_EQUAL_BASE_TYPE(CHAR, data, expected);

#define mcu_assert_not_equal_char(data, expected) \
    MCU_ASSERT_NOT_EQUAL_BASE_TYPE(CHAR, data, expected);






#define MCU_LOG_VALUES_UCHAR(data, expected) \
    MCU_LOG_VALUES(%c, data, expected);

#define mcu_assert_equal_uchar(data, expected) \
    MCU_ASSERT_EQUAL_BASE_TYPE(UCHAR, data, expected);

#define mcu_assert_not_equal_uchar(data, expected) \
    MCU_ASSERT_NOT_EQUAL_BASE_TYPE(UCHAR, data, expected);




#define MCU_LOG_VALUES_SHORT(data, expected) \
    MCU_LOG_VALUES(%i, data, expected);

#define mcu_assert_equal_short(data, expected) \
    MCU_ASSERT_EQUAL_BASE_TYPE(SHORT, data, expected);

#define mcu_assert_not_equal_short(data, expected) \
    MCU_ASSERT_NOT_EQUAL_BASE_TYPE(SHORT, data, expected);



#define MCU_LOG_VALUES_USHORT(data, expected) \
    MCU_LOG_VALUES(%u, data, expected);

#define mcu_assert_equal_ushort(data, expected) \
    MCU_ASSERT_EQUAL_BASE_TYPE(USHORT, data, expected);

#define mcu_assert_not_equal_ushort(data, expected) \
    MCU_ASSERT_NOT_EQUAL_BASE_TYPE(USHORT, data, expected);



///
/// \brief Print the compared int variables by assert_equal_int
///
/// \param[in] data Int variable obtained in the assert test
/// \param[in] expected Int variable expected for the assert test
///
#define MCU_LOG_VALUES_INT(data, expected) \
    MCU_LOG_VALUES(%i, data, expected);

#define mcu_assert_equal_int(data, expected) \
    MCU_ASSERT_EQUAL_BASE_TYPE(INT, data, expected);

#define mcu_assert_not_equal_int(data, expected) \
    MCU_ASSERT_NOT_EQUAL_BASE_TYPE(INT, data, expected);




#define MCU_LOG_VALUES_UINT(data, expected) \
    MCU_LOG_VALUES(%u, data, expected);

#define mcu_assert_equal_uint(data, expected) \
    MCU_ASSERT_EQUAL_BASE_TYPE(UINT, data, expected);

#define mcu_assert_not_equal_uint(data, expected) \
    MCU_ASSERT_NOT_EQUAL_BASE_TYPE(UINT, data, expected);



#define MCU_LOG_VALUES_LONG(data, expected) \
    MCU_LOG_VALUES(%li, data, expected);

#define mcu_assert_equal_long(data, expected) \
    MCU_ASSERT_EQUAL_BASE_TYPE(LONG, data, expected);

#define mcu_assert_not_equal_long(data, expected) \
    MCU_ASSERT_NOT_EQUAL_BASE_TYPE(LONG, data, expected);



#define MCU_LOG_VALUES_ULONG(data, expected) \
    MCU_LOG_VALUES(%lu, data, expected);

#define mcu_assert_equal_ulong(data, expected) \
    MCU_ASSERT_EQUAL_BASE_TYPE(ULONG, data, expected);

#define mcu_assert_not_equal_ulong(data, expected) \
    MCU_ASSERT_NOT_EQUAL_BASE_TYPE(ULONG, data, expected);


#define MCU_LOG_VALUES_ULONG(data, expected) \
    MCU_LOG_VALUES(%lu, data, expected);

#define mcu_assert_equal_ulong(data, expected) \
    MCU_ASSERT_EQUAL_BASE_TYPE(ULONG, data, expected);

#define mcu_assert_not_equal_ulong(data, expected) \
    MCU_ASSERT_NOT_EQUAL_BASE_TYPE(ULONG, data, expected);


#define MCU_LOG_VALUES_LLONG(data, expected) \
    MCU_LOG_VALUES(%lli, data, expected);

#define mcu_assert_equal_llong(data, expected) \
    MCU_ASSERT_EQUAL_BASE_TYPE(LLONG, data, expected);

#define mcu_assert_not_equal_llong(data, expected) \
    MCU_ASSERT_NOT_EQUAL_BASE_TYPE(LLONG, data, expected);


#define MCU_LOG_VALUES_ULLONG(data, expected) \
    MCU_LOG_VALUES(%llu, data, expected);

#define mcu_assert_equal_ullong(data, expected) \
    MCU_ASSERT_EQUAL_BASE_TYPE(ULLONG, data, expected);

#define mcu_assert_not_equal_ullong(data, expected) \
    MCU_ASSERT_NOT_EQUAL_BASE_TYPE(ULLONG, data, expected);


#define MCU_LOG_VALUES_SIZE_T(data, expected) \
    MCU_LOG_VALUES_ULONG(data, expected);

#define mcu_assert_equal_size_t(data, expected) \
    mcu_assert_equal_ulong(data, expected);

#define mcu_assert_not_equal_size_t(data, expected) \
    mcu_assert_not_equal_ulong(data, expected);




#define MCU_LOG_VALUES_PTR(data, expected) \
    MCU_LOG_VALUES(%p, data, expected);

#define mcu_assert_equal_ptr(data, expected) \
    MCU_ASSERT_EQUAL_BASE_TYPE(PTR, data, expected);

#define mcu_assert_not_equal_ptr(data, expected) \
    MCU_ASSERT_NOT_EQUAL_BASE_TYPE(PTR, data, expected);

#define mcu_assert_null_ptr(ptr) \
    MCU_ASSERT_EQUAL_BASE_TYPE(PTR, ptr, NULL);

#define mcu_assert_not_null_ptr(ptr) \
    MCU_ASSERT_NOT_EQUAL_BASE_TYPE(PTR, ptr, NULL);




















///
/// \brief Check within a test_case of a test_suite if two array are "equal" ( based on custom comparison function)
///         One shall not use this MACRO. Internally called by ASSERT_EQUAL_CUSTOM_CMP_ARRAY
///
/// \param[in] test_suite The name of the test_suite where the check is done
/// \param[in] test_case The name of the test_case where the check is done
/// \param[in] cmp_function Hookup function which does the comparison of data and expected variables
/// \param[in] data The first array for comparison
/// \param[in] expected The second array for comparison
/// \param[in] size The length of both arrays
/// \param[in] message The message to print in case of failed test
///
#define ASSERT_EQUAL_CUSTOM_CMP_ARRAY_BASE(test_suite, test_case, cmp_function, data, expected, size, message)                            \
    do {                                                              \
        *nb_tests+=1;                                                 \
        if (!((cmp_function)((data), (expected), size))) {                                \
            *nb_failed+=1;                                              \
            MCU_LOG_BASE(__FILENAME__, test_suite, test_case, __LINE__, message);  \
        }                                                             \
    } while (0)


///
/// \brief Check if two arrays are "equal" ( based on custom comparison function)
///         Shall be used inside a TEST_CASE. Abstraction of BASE macro
///
/// \param[in] cmp_function Hookup function which does the comparison of data and expected variables
/// \param[in] data The first array for comparison
/// \param[in] expected The second array for comparison
/// \param[in] size The length of both arrays
///
#define ASSERT_EQUAL_CUSTOM_CMP_ARRAY(cmp_function, data, expected, size)                            \
    ASSERT_EQUAL_CUSTOM_CMP_ARRAY_BASE(test_suite, __func__, cmp_function, data, expected, size, "\""#data" == "#expected"\"")


///
/// \brief Check if two arrays are "equal" ( based on custom comparison function)
///         Print custom message if assert fails
///         Shall be used inside a TEST_CASE. Abstraction of BASE macro
///
/// \param[in] cmp_function Hookup function which does the comparison of data and expected variables
/// \param[in] data The first array for comparison
/// \param[in] expected The second array for comparison
/// \param[in] size The length of both arrays
/// \param[in] message The message to print in case of failed test
///
#define ASSERT_EQUAL_CUSTOM_CMP_ARRAY_MESSAGE(cmp_function, data, expected, size, message)                            \
    ASSERT_EQUAL_CUSTOM_CMP_ARRAY_BASE(test_suite, __func__, cmp_function, data, expected, size, message)




















///
/// \brief Initial definition of a test case.
///         Create C function to hold the tests of one test case (can be one feature to test, one path, one function)
///         Shadows the use of counters for number of tests, function naming and test report for the user
///
/// \param[in] name shortname of the test_case
///
#define TEST_CASE_BEGIN(name) \
    void test_case_##name(const char* const test_suite, size_t* nb_tests, size_t* nb_failed) \
    { \
        size_t start_nb_tests = *nb_tests;        \
        size_t start_nb_failed = *nb_failed;      \
        LOG_FUNCTION("TEST CASE %s...\n", ""#name"");  \
        LOG_FUNCTION("---\n");

///
/// \brief Finalize the  definition of a test case.
///         Shadows the use of counters for number of tests , function naming, and test report for the user
///
///
#define TEST_CASE_END() \
        size_t nb_test_tc = *nb_tests - start_nb_tests; \
        size_t nb_test_tc_failed = *nb_failed - start_nb_failed; \
        size_t nb_test_tc_passed = nb_test_tc - nb_test_tc_failed; \
        \
        if (nb_test_tc_failed > 0)    \
        {   \
            LOG_FUNCTION("--- KO - %lu tests : %lu passed, %lu failed ---\n", nb_test_tc, nb_test_tc_passed, nb_test_tc_failed); \
            LOG_FUNCTION("\n"); \
        }   \
        else    \
        {   \
            LOG_FUNCTION("--- OK - %lu passed ---\n", nb_test_tc_passed); \
            LOG_FUNCTION("\n"); \
        }   \
    }



///
/// \brief Execute a test_case
///
/// \warning To be used only inside test suite
///
/// \param[in] name shortname of the test_case to run
///
#define TEST_CASE_RUN(tc) \
    do { \
        test_case_##tc(__func__, &nbr_tests, &nbr_failed); \
    } while (0)



///
/// \brief Declaration of a test suite. The name shall perfectly match the one used in TEST_SUITE_BEGIN
///         To be used in .h file or in main.c filef or lazyness
///
/// \param[in] name shortname of the test_suite
///
#define EXTERNAL_DECLARE_TEST_SUITE(name) \
    extern const char* test_suite_##name()


///
/// \brief Initial definition of a test suite.
///         Create C function to run the different test cases of the suite (can be one function to test with multiple input datasets, multiple paths etc..)
///         Shadows the use of counters for number of tests, function naming and test report for the user
///
/// \param[in] name shortname of the test_suite
///
#define TEST_SUITE_BEGIN(name) \
    const char* test_suite_##name() \
    { \
        size_t nbr_tests = 0; \
        size_t nbr_failed = 0;    \
        LOG_FUNCTION("TEST SUITE %s \n", ""#name"");   \
        LOG_FUNCTION("===========================================================\n");


///
/// \brief Finalize the  definition of a test suite.
///         Shadows the use of counters for number of tests , function naming, and test report for the user
///
///
#define TEST_SUITE_END() \
        if(nbr_failed != 0) \
        { \
            LOG_FUNCTION("================ KO - %lu tests :  %lu passed, %lu failed =================\n\n", nbr_tests, nbr_tests - nbr_failed, nbr_failed); \
            return "KO"; \
        } \
        else \
        { \
            LOG_FUNCTION("================ OK -  %lu passed =================\n\n", nbr_tests); \
            return "OK"; \
        } \
    }


///
/// \brief Execute a test_suite with no group reporting
///         Shall NOT be used directly. Use TEST_SUITE_RUN instead
///
/// \warning This is the only macro that does not use do {} while (0) trick because it it expanded inside another functions
///
/// \param[in] name shortname of the test_case to run
///
#define TEST_SUITE_RUN_OUT_OF_GROUP(name) \
    test_suite_##name()


///
/// \brief Execute a test_suite with  group reporting
///         Shall NOT be used directly. Use TEST_SUITE_RUN instead
///
/// \param[in] name shortname of the test_case to run
///
#define TEST_SUITE_RUN_IN_GROUP(name) \
    do { \
        strcat(group_report, ""#name""); \
        strcat(group_report, "..."); \
        strcat(group_report, TEST_SUITE_RUN_OUT_OF_GROUP(name)); \
        strcat(group_report, "\n"); \
    } while (0)


///
/// \brief Execute a test_suite with no group reporting
///
/// \param[in] name shortname of the test_case to run
///
#define TEST_SUITE_RUN(name) \
    do { \
        if (group_report[0] == '\0') \
        { \
            TEST_SUITE_RUN_OUT_OF_GROUP(name); \
        } \
        else \
        { \
            TEST_SUITE_RUN_IN_GROUP(name); \
        } \
    } while (0)



///
/// \brief Initialize the log report for overview of all test_suites report (only OK/KO with no verbosity)
///
/// \param[in] name The name of the group of test_suites
///
#define TEST_GROUP_INITIALIZE(name) \
    do { \
        sprintf(group_report, "UNITTEST GROUP %s \n**********\n", ""#name""); \
    } while (0)


/// \brief Finalize and print the log report for overview of all test_suites report (only OK/KO with no verbosity)
///
///
#define TEST_GROUP_FINALIZE() \
    do { \
        LOG_FUNCTION(group_report); \
    } while (0)

#endif  /*  __MINICUTEST_H__ */