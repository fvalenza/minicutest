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

// For print formating : https://fr.wikipedia.org/wiki/Types_de_donn%C3%A9e_du_langage_C


////////////////////////////////////////////////////////////////////
///                                                              ///
///                   USER REDEFINED BEHAVIOR                    ///
///                                                              ///
////////////////////////////////////////////////////////////////////

#ifndef CUSTOM_PRINT_METHOD
#define LOG_FUNCTION printf
#else
#define LOG_FUNCTION CUSTOM_PRINT_METHOD
#endif

#ifndef VERBOSITY_USER
#define VERBOSITY_USER (0x0)
#endif

#define VERBOSITY ( (VERBOSITY_USER & 0x01) )



////////////////////////////////////////////////////////////////////
///                                                              ///
///                       GLOBAL VARIABLES                       ///
///                                                              ///
////////////////////////////////////////////////////////////////////

// For all ANSI colors, see https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
// #define URED   "\x1B[4;31m" --> just add the modifier (here : 4 for underlining)
#ifdef ANSI_NOT_SUPPORTED
    #define RED   ""
    #define GRN   ""
    #define YEL   ""
    #define BLU   ""
    #define MAG   ""
    #define CYN   ""
    #define WHT   ""
    #define RESET ""
#else
    #define RED   "\x1B[31m"
    #define GRN   "\x1B[32m"
    #define YEL   "\x1B[33m"
    #define BLU   "\x1B[34m"
    #define MAG   "\x1B[35m"
    #define CYN   "\x1B[36m"
    #define WHT   "\x1B[37m"
    #define RESET "\x1B[0m"
#endif

#define TEST_PASSED "PASSED"
#define TEST_FAILED "FAILED"


///
/// \brief Array of char to store log report of TEST_GROUP
///
static char group_report[500000]; // should be long enough to hold full report


////////////////////////////////////////////////////////////////////
///                                                              ///
///                     REPORTING FUNCTIONS                      ///
///                                                              ///
////////////////////////////////////////////////////////////////////

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

///
/// \brief Basic print/log function for assert reporting.
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
/// \brief Print the expected and obtained values based on printf formatting
///
/// \param[in] type The formatting type of the variables to print
/// \param[in] data Variable obtained
/// \param[in] expected Variable expected
///
#define MCU_LOG_VALUES(type, data, expected) \
    do { \
        if (VERBOSITY) \
        { \
            LOG_FUNCTION(MAG "Expected " #type " , obtained " #type RESET "\n", expected, data); \
        } \
    } while (0)

///
/// \brief Print the user-defined message
///
#define mcu_log(message) \
    LOG_FUNCTION("%s\n", message)


//-----------------------//
//------- LOG API -------//
//-----------------------//

///
/// \brief Print the compared variables in the form "Expected = x, obtained = y"
///         Call base macro with the right formating depending on type
///
#define mcu_log_values_char(data, expected) \
    MCU_LOG_VALUES(%c, data, expected)

#define mcu_log_values_uchar(data, expected) \
    MCU_LOG_VALUES(%c, data, expected)

#define mcu_log_values_short(data, expected) \
    MCU_LOG_VALUES(%i, data, expected)

#define mcu_log_values_ushort(data, expected) \
    MCU_LOG_VALUES(%u, data, expected)

#define mcu_log_values_int(data, expected) \
    MCU_LOG_VALUES(%i, data, expected)

#define mcu_log_values_uint(data, expected) \
    MCU_LOG_VALUES(%u, data, expected)

#define mcu_log_values_long(data, expected) \
    MCU_LOG_VALUES(%li, data, expected)

#define mcu_log_values_ulong(data, expected) \
    MCU_LOG_VALUES(%lu, data, expected)

#define mcu_log_values_llong(data, expected) \
    MCU_LOG_VALUES(%lli, data, expected)

#define mcu_log_values_ullong(data, expected) \
    MCU_LOG_VALUES(%llu, data, expected)

#define mcu_log_values_string(data, expected) \
    MCU_LOG_VALUES(%s, data, expected)

#define mcu_log_values_ptr(data, expected) \
    MCU_LOG_VALUES(%p, data, expected)

#define mcu_log_values_size_t(data, expected) \
    MCU_LOG_VALUES(%lu, data, expected)

#define mcu_log_values_float(data, expected) \
    MCU_LOG_VALUES(%f, data, expected)

#define mcu_log_values_double(data, expected) \
    MCU_LOG_VALUES(%lf, data, expected)





////////////////////////////////////////////////////////////////////
///                                                              ///
///                    ASSERT functionalities                    ///
///                                                              ///
////////////////////////////////////////////////////////////////////





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
            MCU_LOG_BASE(__FILENAME__, test_suite, test_case, __LINE__, message)  \
        }                                                             \
    } while (0)



///
/// \brief Base macro for testing equality of two variables. For type for which true == is possible
///         Prints values in case of error (with the good format for print)
///         One shall not use this MACRO. Internally called by other assert macros
///
#define MCU_ASSERT_EQUAL_TYPE_BASE(TYPE, data, expected)                            \
    do { \
        size_t nb_failed_before = *nb_failed; \
        MCU_ASSERT_BASE(test_suite, __func__, ((data) == (expected)), "\""#data" == "#expected"\""); \
        if (*nb_failed - nb_failed_before == 1) \
        { \
            mcu_log_values_##TYPE((data), (expected)); \
        } \
    } while (0)


///
/// \brief Base macro for testing that two variables are not equal. For type for which true == is possible
///         Prints values in case of error (with the good format for print)
///         One shall not use this MACRO. Internally called by other assert macros
///
#define MCU_ASSERT_NOT_EQUAL_TYPE_BASE(TYPE, data, expected)                            \
    do { \
        size_t nb_failed_before = *nb_failed; \
        MCU_ASSERT_BASE(test_suite, __func__, (!((data) == (expected))), "\""#data" != "#expected"\""); \
        if (*nb_failed - nb_failed_before == 1) \
        { \
            mcu_log_values_##TYPE((data), (expected)); \
        } \
    } while (0)


///
/// \brief Base macro for testing that two strings are equal.
///         Prints values in case of error (with the good format for print)
///         One shall not use this MACRO. Internally called by other assert macros
///
#define MCU_ASSERT_EQUAL_STRING_BASE(data, expected) \
    do { \
        size_t nb_failed_before = *nb_failed; \
        MCU_ASSERT_BASE(test_suite, __func__, (strcmp((data), (expected)) == 0), "\""#data" == "#expected"\""); \
        if (*nb_failed - nb_failed_before == 1) \
        { \
            mcu_log_values_string((data), (expected)); \
        } \
    } while (0)


///
/// \brief Base macro for testing that two strings are not equal.
///         Prints values in case of error (with the good format for print)
///         One shall not use this MACRO. Internally called by other assert macros
///
#define MCU_ASSERT_NOT_EQUAL_STRING_BASE(data, expected) \
    do { \
        size_t nb_failed_before = *nb_failed; \
        MCU_ASSERT_BASE(test_suite, __func__, (!(strcmp((data), (expected)) == 0)), "\""#data" != "#expected"\""); \
        if (*nb_failed - nb_failed_before == 1) \
        { \
            mcu_log_values_string((data), (expected)); \
        } \
    } while (0)



///
/// \brief Base macro for testing that two floats are equal.
///         Prints values in case of error (with the good format for print)
///         One shall not use this MACRO. Internally called by other assert macros
///
#define MCU_ASSERT_EQUAL_FLOAT_BASE(data, expected, precision) \
    do { \
        const float float_diff = (((data) - (expected)) < 0) ? -((data) - (expected)) : ((data) - (expected)); \
        size_t nb_failed_before = *nb_failed; \
        MCU_ASSERT_BASE(test_suite, __func__, (float_diff <= precision), "\""#data" == "#expected"\""); \
        if (*nb_failed - nb_failed_before == 1) \
        { \
            mcu_log_values_float((data), (expected)); \
        } \
    } while (0)


///
/// \brief Base macro for testing that two floats are not equal.
///         Prints values in case of error (with the good format for print)
///         One shall not use this MACRO. Internally called by other assert macros
///
#define MCU_ASSERT_NOT_EQUAL_FLOAT_BASE(data, expected, precision) \
    do { \
        const float float_diff = (((data) - (expected)) < 0) ? -((data) - (expected)) : ((data) - (expected)); \
        size_t nb_failed_before = *nb_failed; \
        MCU_ASSERT_BASE(test_suite, __func__, (float_diff > precision), "\""#data" != "#expected"\""); \
        if (*nb_failed - nb_failed_before == 1) \
        { \
            mcu_log_values_float((data), (expected)); \
        } \
    } while (0)


///
/// \brief Base macro for testing that two doubles are equal.
///         Prints values in case of error (with the good format for print)
///         One shall not use this MACRO. Internally called by other assert macros
///
#define MCU_ASSERT_EQUAL_DOUBLE_BASE(data, expected, precision) \
    do { \
        const double double_diff = (((data) - (expected)) < 0) ? -((data) - (expected)) : ((data) - (expected)); \
        size_t nb_failed_before = *nb_failed; \
        MCU_ASSERT_BASE(test_suite, __func__, (double_diff <= precision), "\""#data" == "#expected"\""); \
        if (*nb_failed - nb_failed_before == 1) \
        { \
            mcu_log_values_double((data), (expected)); \
        } \
    } while (0)


///
/// \brief Base macro for testing that two doubles are equal.
///         Prints values in case of error (with the good format for print)
///         One shall not use this MACRO. Internally called by other assert macros
///
#define MCU_ASSERT_NOT_EQUAL_DOUBLE_BASE(data, expected, precision) \
    do { \
        const double double_diff = (((data) - (expected)) < 0) ? -((data) - (expected)) : ((data) - (expected)); \
        size_t nb_failed_before = *nb_failed; \
        MCU_ASSERT_BASE(test_suite, __func__, (double_diff > precision), "\""#data" != "#expected"\""); \
        if (*nb_failed - nb_failed_before == 1) \
        { \
            mcu_log_values_double((data), (expected)); \
        } \
    } while (0)


///
/// \brief Base macro for testing that two arrays are equal. This macro will test the expr for each index.
///         Prints values in case of error (with the good format for print)
///         One shall not use this MACRO. Internally called by other assert macros
///
/// \param[in] data  The first array of the comparison. Used only for displaying failure message
/// \param[in] expected The expected array of the comparison. Used only for displaying failure message
/// \param[in] expr  the comparison expression. Must be built by calling-macro knowing in advance how to test the arrays
/// \param[in] size Length of the arrays
///
#define MCU_ASSERT_EQUAL_ARRAY_BASE(data, expected, expr, size) \
    do \
    { \
        *nb_tests+=1;  \
        int nb_array_tests_failed = 0; \
        for (size_t idx = 0; idx < size; ++idx) \
        { \
            if ((expr)) \
            { \
                ++nb_array_tests_failed; \
            } \
        } \
        if (nb_array_tests_failed > 0) \
        { \
            *nb_failed+=1; \
            char array_test_results[1024]; \
            sprintf(array_test_results,  "\""#data" != "#expected"\" : " MAG "%u ko / %u " RESET , nb_array_tests_failed, size); \
            MCU_LOG_BASE(__FILENAME__, test_suite, __func__, __LINE__, array_test_results)  \
        } \
    } while(0)



//-----------------------//
//------ ASSERT API -----//
//-----------------------//

#define mcu_assert_true(expr) \
    MCU_ASSERT_BASE(test_suite, __func__, (expr), "\""#expr" is not true\"")


#define mcu_assert_false(expr) \
    MCU_ASSERT_BASE(test_suite, __func__, !(expr), "\""#expr" is true\"")

#define mcu_assert(expr) \
    mcu_assert_true(expr)

#define mcu_assert_message(expr, message) \
    MCU_ASSERT_BASE(test_suite, __func__, (expr), message)




#define mcu_assert_equal_char(data, expected) \
    MCU_ASSERT_EQUAL_TYPE_BASE(char, data, expected)

#define mcu_assert_not_equal_char(data, expected) \
    MCU_ASSERT_NOT_EQUAL_TYPE_BASE(char, data, expected)


#define mcu_assert_equal_uchar(data, expected) \
    MCU_ASSERT_EQUAL_TYPE_BASE(uchar, data, expected)

#define mcu_assert_not_equal_uchar(data, expected) \
    MCU_ASSERT_NOT_EQUAL_TYPE_BASE(uchar, data, expected)


#define mcu_assert_equal_short(data, expected) \
    MCU_ASSERT_EQUAL_TYPE_BASE(short, data, expected)

#define mcu_assert_not_equal_short(data, expected) \
    MCU_ASSERT_NOT_EQUAL_TYPE_BASE(short, data, expected)


#define mcu_assert_equal_ushort(data, expected) \
    MCU_ASSERT_EQUAL_TYPE_BASE(ushort, data, expected)

#define mcu_assert_not_equal_ushort(data, expected) \
    MCU_ASSERT_NOT_EQUAL_TYPE_BASE(ushort, data, expected)


#define mcu_assert_equal_int(data, expected) \
    MCU_ASSERT_EQUAL_TYPE_BASE(int, data, expected)

#define mcu_assert_not_equal_int(data, expected) \
    MCU_ASSERT_NOT_EQUAL_TYPE_BASE(int, data, expected)


#define mcu_assert_equal_uint(data, expected) \
    MCU_ASSERT_EQUAL_TYPE_BASE(uint, data, expected)

#define mcu_assert_not_equal_uint(data, expected) \
    MCU_ASSERT_NOT_EQUAL_TYPE_BASE(uint, data, expected)


#define mcu_assert_equal_long(data, expected) \
    MCU_ASSERT_EQUAL_TYPE_BASE(long, data, expected)

#define mcu_assert_not_equal_long(data, expected) \
    MCU_ASSERT_NOT_EQUAL_TYPE_BASE(long, data, expected)


#define mcu_assert_equal_ulong(data, expected) \
    MCU_ASSERT_EQUAL_TYPE_BASE(ulong, data, expected)

#define mcu_assert_not_equal_ulong(data, expected) \
    MCU_ASSERT_NOT_EQUAL_TYPE_BASE(ulong, data, expected)


#define mcu_assert_equal_ulong(data, expected) \
    MCU_ASSERT_EQUAL_TYPE_BASE(ulong, data, expected)

#define mcu_assert_not_equal_ulong(data, expected) \
    MCU_ASSERT_NOT_EQUAL_TYPE_BASE(ulong, data, expected)


#define mcu_assert_equal_llong(data, expected) \
    MCU_ASSERT_EQUAL_TYPE_BASE(llong, data, expected)

#define mcu_assert_not_equal_llong(data, expected) \
    MCU_ASSERT_NOT_EQUAL_TYPE_BASE(llong, data, expected)


#define mcu_assert_equal_ullong(data, expected) \
    MCU_ASSERT_EQUAL_TYPE_BASE(ullong, data, expected)

#define mcu_assert_not_equal_ullong(data, expected) \
    MCU_ASSERT_NOT_EQUAL_TYPE_BASE(ullong, data, expected)


#define mcu_assert_equal_string(data, expected) \
    MCU_ASSERT_EQUAL_STRING_BASE(data, expected)

#define mcu_assert_not_equal_string(data, expected) \
    MCU_ASSERT_NOT_EQUAL_STRING_BASE(data, expected)


#define mcu_assert_equal_ptr(data, expected) \
    MCU_ASSERT_EQUAL_TYPE_BASE(ptr, data, expected)

#define mcu_assert_not_equal_ptr(data, expected) \
    MCU_ASSERT_NOT_EQUAL_TYPE_BASE(ptr, data, expected)

#define mcu_assert_null_ptr(pointer) \
    MCU_ASSERT_EQUAL_TYPE_BASE(ptr, pointer, NULL)

#define mcu_assert_not_null_ptr(pointer) \
    MCU_ASSERT_NOT_EQUAL_TYPE_BASE(ptr, pointer, NULL)


#define mcu_assert_equal_size_t(data, expected) \
    mcu_assert_equal_ulong(data, expected)

#define mcu_assert_not_equal_size_t(data, expected) \
    mcu_assert_not_equal_ulong(data, expected)


#define mcu_assert_equal_float(data, expected, precision) \
    MCU_ASSERT_EQUAL_FLOAT_BASE(data, expected, precision)

// expects the relative_precision expressed in %
#define mcu_assert_equal_float_rel(data, expected, rel_precision) \
    MCU_ASSERT_EQUAL_FLOAT_BASE(data, expected, ((rel_precision) * ((expected) < 0.0 ? -(expected) : (expected)) ))


#define mcu_assert_equal_double(data, expected, precision) \
    MCU_ASSERT_EQUAL_DOUBLE_BASE(data, expected, precision)

// expects the relative_precision expressed in %
#define mcu_assert_equal_double_rel(data, expected, rel_precision) \
    MCU_ASSERT_EQUAL_DOUBLE_BASE(data, expected, ((rel_precision) * ((expected) < 0.0 ? -(expected) : (expected)) ))



///
/// \brief Check if two variables are "equal" based on custom comparison function
///
/// \param[in] cmp_function Hookup function which does the comparison of data and expected variables
///
#define mcu_assert_equal_custom_cmp(cmp_function, data, expected) \
    MCU_ASSERT_BASE(test_suite, __func__, ((cmp_function)((data), (expected))), "\""#data" == "#expected"\"")

#define mcu_assert_not_equal_custom_cmp(cmp_function, data, expected) \
    MCU_ASSERT_BASE(test_suite, __func__, !((cmp_function)((data), (expected))), "\""#data" != "#expected"\"")

///
/// \brief Check if two variables are "equal" based on custom comparison function
///         Prints custom message if assert fails
///
/// \param[in] cmp_function Hookup function which does the comparison of data and expected variables
///
#define mcu_assert_equal_custom_cmp_message(cmp_function, data, expected, message) \
    MCU_ASSERT_BASE(test_suite, __func__, ((cmp_function)((data), (expected))), message)



#define mcu_assert_equal_int_array(data, expected, size) \
    MCU_ASSERT_EQUAL_ARRAY_BASE(data, expected, !((data)[idx] == (expected)[idx]), size)

#define mcu_assert_equal_int_array_each(data, expected, size) \
    MCU_ASSERT_EQUAL_ARRAY_BASE(data, expected, !((data)[idx] == (expected)), size)

#define mcu_assert_equal_custom_cmp_array(cmp_function, data, expected, size) \
    MCU_ASSERT_EQUAL_ARRAY_BASE(data, expected, !((cmp_function)(((data)[idx]), ((expected)[idx]))), size)

#define mcu_assert_equal_custom_cmp_array_each(cmp_function, data, expected, size) \
    MCU_ASSERT_EQUAL_ARRAY_BASE(data, expected, !((cmp_function)(((data)[idx]), (expected))), size)

#define mcu_assert_equal_float_array(data, expected, precision, size) \
    MCU_ASSERT_EQUAL_ARRAY_BASE(data, expected, (((data)[idx] - (expected)[idx]) < 0 ? ((expected)[idx] - (data)[idx]) : ((data)[idx] - (expected)[idx])) > (precision), size)

#define mcu_assert_equal_float_array_each(data, expected, precision, size) \
    MCU_ASSERT_EQUAL_ARRAY_BASE(data, expected, (((data)[idx] - (expected)) < 0 ? ((expected) - (data)[idx]) : ((data)[idx] - (expected))) > (precision), size)






////////////////////////////////////////////////////////////////////
///                                                              ///
///     DECLARATION AND EXECUTION OF TEST_CASES and TEST_SUITES  ///
///                                                              ///
////////////////////////////////////////////////////////////////////


///
/// \brief Initial definition of a test case.
///         Create C function to hold the tests of one test case (can be one feature to test, one path, one function)
///         Shadows the use of counters for number of tests, function naming and test report for the user
///
/// \param[in] name shortname of the test_case
///
#define TEST_CASE_BEGIN(name) \
    static void test_case_##name(const char* const test_suite, size_t* nb_tests, size_t* nb_failed) \
    { \
        size_t start_nb_tests = *nb_tests;        \
        size_t start_nb_failed = *nb_failed;      \
        LOG_FUNCTION(CYN "TEST CASE %s...\n" RESET, ""#name"");  \
        LOG_FUNCTION(CYN "---\n" RESET);

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
            LOG_FUNCTION(CYN "--- " RED TEST_FAILED RESET" - %lu tests : %lu passed, %lu failed " CYN "---\n" RESET, nb_test_tc, nb_test_tc_passed, nb_test_tc_failed); \
            LOG_FUNCTION("\n"); \
        }   \
        else    \
        {   \
            LOG_FUNCTION(CYN "--- " GRN TEST_PASSED RESET " - %lu passed " CYN " ---\n" RESET , nb_test_tc_passed); \
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
#define test_case_run(tc) \
    test_case_##tc(__func__, &nbr_tests, &nbr_failed)



///
/// \brief Declaration of a test suite. The name shall perfectly match the one used in TEST_SUITE_BEGIN
///         To be used in .h file or in main.c filef or lazyness
///
/// \param[in] name shortname of the test_suite
///
#define external_declare_test_suite(name) \
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
        LOG_FUNCTION(YEL "TEST SUITE %s \n" RESET, ""#name"");   \
        LOG_FUNCTION(YEL "===========================================================\n" RESET);


///
/// \brief Finalize the  definition of a test suite.
///         Shadows the use of counters for number of tests , function naming, and test report for the user
///
///
#define TEST_SUITE_END() \
        if(nbr_failed != 0) \
        { \
            LOG_FUNCTION( YEL "================ KO - %lu tests :  %lu passed, %lu failed =================\n\n" RESET, nbr_tests, nbr_tests - nbr_failed, nbr_failed); \
            return TEST_FAILED; \
        } \
        else \
        { \
            LOG_FUNCTION(YEL "================ OK -  %lu passed =================\n\n" RESET, nbr_tests); \
            return TEST_PASSED; \
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
        if ( strcmp(TEST_SUITE_RUN_OUT_OF_GROUP(name), TEST_PASSED) == 0 ) \
        { \
            strcat(group_report, GRN); \
            strcat(group_report, TEST_PASSED); \
        } \
        else \
        { \
            strcat(group_report, RED); \
            strcat(group_report, TEST_FAILED); \
        } \
        strcat(group_report, RESET); \
        strcat(group_report, "\n"); \
    } while (0)


///
/// \brief Execute a test_suite with no group reporting
///
/// \param[in] name shortname of the test_case to run
///
#define test_suite_run(name) \
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
#define test_group_initialize(name) \
    do { \
        sprintf(group_report, "UNITTEST GROUP %s \n**********\n", ""#name""); \
    } while (0)


/// \brief Finalize and print the log report for overview of all test_suites report (only OK/KO with no verbosity)
///
///
#define test_group_finalize() \
    do { \
        LOG_FUNCTION(group_report); \
    } while (0)

#endif  /*  __MINICUTEST_H__ */