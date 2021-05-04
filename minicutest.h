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
#include <string.h>


// For usage of do{} while(0) with NO semicolon at the end of the macro (hence user shall put semicolon after each macro call)
// see http://c-faq.com/cpp/multistmt.html


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
///         Builds the message with usefull information of where the assert has failed and call LOG_FUNCTION
///
/// \param[in] filename Name of the file where this macro is called
/// \param[in] test_suite Name of the test_suite where this macro is called
/// \param[in] test_case Name of the test_case where this macro is called
/// \param[in] line Line of the source file where this macro is called
/// \param[in] message The message to print
///
#define ASSERT_LOG(filename, test_suite, test_case, line, message) \
    LOG_FUNCTION("%s::%s::%s:%u - Assertion failed : %s \n", filename, test_suite, test_case, line, message)


///
/// \brief Print the compared int variables by assert_equal_int
///
/// \param[in] data Int variable obtained in the assert test
/// \param[in] expected Int variable expected for the assert test
///
#define ASSERT_LOG_VALUES_INT(data, expected) \
    do { \
        if (VERBOSITY) \
        { \
            LOG_FUNCTION("Expected %i , obtained %i\n", expected, data); \
        } \
    } while (0)


///
/// \brief Check within a test_case of a test_suite if two integers are equal
///         One shall not use this MACRO. Internally called by ASSERT_EQUAL_INT
///
/// \param[in] test_suite The name of the test_suite where the check is done
/// \param[in] test_case The name of the test_case where the check is done
/// \param[in] data The first integer for comparison
/// \param[in] expected The second integer for comparison
/// \param[in] message The message to print in case of failed test
///
#define ASSERT_EQUAL_INT_BASE(test_suite, test_case, data, expected, message)                            \
    do {                                                              \
        *nb_tests+=1;                                                 \
        if ( (data) != (expected) ) {                                \
            *nb_failed+=1;                                              \
            ASSERT_LOG(__FILENAME__, test_suite, test_case, __LINE__, message);  \
            ASSERT_LOG_VALUES_INT(data, expected); \
        }                                                             \
    } while (0)

///
/// \brief Check within a test_case of a test_suite if two integers are equal
///         Shall be used inside a TEST_CASE. Abstraction of BASE macro
///
/// \param[in] data The first integer for comparison
/// \param[in] expected The second integer for comparison
///
#define ASSERT_EQUAL_INT(data, expected) \
    ASSERT_EQUAL_INT_BASE(test_suite, __func__, data, expected, "\""#data" == "#expected"\"")

///
/// \brief Check within a test_case of a test_suite if two integers are equal
///         Print custom message if assert fails
///         Shall be used inside a TEST_CASE. Abstraction of BASE macro
///
/// \param[in] data The first integer for comparison
/// \param[in] expected The second integer for comparison
/// \param[in] message The message to print in case of failed test
///
#define ASSERT_EQUAL_INT_MESSAGE(data, expected, message) \
    ASSERT_EQUAL_INT_BASE(test_suite, __func__, data, expected, message)


///
/// \brief Check within a test_case of a test_suite if two variables are "equal" ( based on custom comparison function)
///         One shall not use this MACRO. Internally called by ASSERT_EQUAL_CUSTOM_CMP
///
/// \param[in] test_suite The name of the test_suite where the check is done
/// \param[in] test_case The name of the test_case where the check is done
/// \param[in] cmp_function Hookup function which does the comparison of data and expected variables. Should return C-True like if cmp equal
/// \param[in] data The first variable for comparison
/// \param[in] expected The second variable for comparison
/// \param[in] message The message to print in case of failed test
///
#define ASSERT_EQUAL_CUSTOM_CMP_BASE(test_suite, test_case, cmp_function, data, expected, message)                            \
    do {                                                              \
        *nb_tests+=1;                                                 \
        if (!((cmp_function)((data), (expected)))) {                                \
            *nb_failed+=1;                                              \
            ASSERT_LOG(__FILENAME__, test_suite, test_case, __LINE__, message);  \
        }                                                             \
    } while (0)

///
/// \brief Check if two variables are "equal" ( based on custom comparison function)
///         Shall be used inside a TEST_CASE. Abstraction of BASE macro
///
/// \param[in] cmp_function Hookup function which does the comparison of data and expected variables
/// \param[in] data The first variable for comparison
/// \param[in] expected The second variable for comparison
///
#define ASSERT_EQUAL_CUSTOM_CMP(cmp_function, data, expected) \
    ASSERT_EQUAL_CUSTOM_CMP_BASE(test_suite, __func__, cmp_function, data, expected, "\""#data" == "#expected"\"")

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
#define ASSERT_EQUAL_CUSTOM_CMP_MESSAGE(cmp_function, data, expected, message) \
    ASSERT_EQUAL_CUSTOM_CMP_BASE(test_suite, __func__, cmp_function, data, expected, message)

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
            ASSERT_LOG(__FILENAME__, test_suite, test_case, __LINE__, message);  \
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
    void test_case_##name(const char* const test_suite, uint32_t* nb_tests, uint32_t* nb_failed) \
    { \
        uint32_t start_nb_tests = *nb_tests;        \
        uint32_t start_nb_failed = *nb_failed;      \
        LOG_FUNCTION("TEST CASE %s...\n", ""#name"");  \
        LOG_FUNCTION("---\n");

///
/// \brief Finalize the  definition of a test case.
///         Shadows the use of counters for number of tests , function naming, and test report for the user
///
///
#define TEST_CASE_END() \
        uint32_t nb_test_tc = *nb_tests - start_nb_tests; \
        uint32_t nb_test_tc_failed = *nb_failed - start_nb_failed; \
        uint32_t nb_test_tc_passed = nb_test_tc - nb_test_tc_failed; \
        \
        if (nb_test_tc_failed > 0)    \
        {   \
            LOG_FUNCTION("--- KO - %u tests : %u passed, %u failed ---\n", nb_test_tc, nb_test_tc_passed, nb_test_tc_failed); \
            LOG_FUNCTION("\n"); \
        }   \
        else    \
        {   \
            LOG_FUNCTION("--- OK - %u passed ---\n", nb_test_tc_passed); \
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
        uint32_t nbr_tests = 0; \
        uint32_t nbr_failed = 0;    \
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
            LOG_FUNCTION("================ KO - %u tests :  %u passed, %u failed =================\n\n", nbr_tests, nbr_tests - nbr_failed, nbr_failed); \
            return "KO"; \
        } \
        else \
        { \
            LOG_FUNCTION("================ OK -  %u passed =================\n\n", nbr_tests); \
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