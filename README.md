# minicutest

MINImalist C UnitTEST framework

Minicutest is a header-only C unittest framework built with the objective to offer unittesting capabilities and reporting. With a primary focus on being minimalist, small and portable(WIP for portability).

No installation, no external compilation, no linking is needed. Just include the header and you're ready to set up a simple yet effective testing environment.


## Setting up basic unittests using minicutest

In order to start building unittests, the steps are straightforward:

1/ Include the header file in your project. Do not forget to add path in your compilation settings if you do not copy the file in your project but install it somewhere else

```c
#include <minicutest.h>
``` 

2/ Set up test suite + test cases
We then need to create the atomic unittests (and separate them into test cases) and create the test suite thaat will execute all the test cases.

```c
// To initialize a test case. Uppercase macro means __no semicolon at the end of the line__
TEST_CASE_BEGIN(string_test_case)

	const char string1[10] = "Hello";
	const char string2[10] = "World";
	const char string3[10] = "World";

	mcu_assert_equal_string(string1, string2);  // Test equality of string1 with string2. Lowercase macro means __need of semicolon at the end of the line__
	mcu_assert_equal_string(string3, string2);
	mcu_assert_not_equal_string(string3, string2);

// To finalize the test case
TEST_CASE_END()


// To initialize a test suite
TEST_SUITE_BEGIN(mcu_suite1)

	test_case_run(string_test_case); // To execute a test_case

// To finalize a test suite
TEST_SUITE_END()
```

3/ Call the test suite in you main 

```c

int main() {

	// To initialize the overview reporting functionality when running LOT a test_suites
	test_group_initialize(example_minicutest_ts_group);
	
	test_suite_run(mcu_suite1); // To execute a test_suite

	// To finalize and display to overview reporting
	test_group_finalize();
	
	return(0);
}
```

## Functionalities

This section is not exhaustive but is meant to understand the conventions used by this library:

One can find four types of macros with this library:

- An API to setup the unittest framework (uppercase macros to initialize/finalize test_cases, test_suites, test_group)
- An API to do some logging (lowercase macros )
- An API to do assertions (lowercase macros)
- Core macro (usually suffixed "\_BASE" in the code). These are internal macros and shall be used only internally

### Uppercase vs Lowercase macros

By looking at the library, you can find uppercase and lowercase macros.
Uppercase macros are meant to be used by the user WITHOUT semicolon at the end. The only uppercase macros that one should use are for test_case and test_suite initialize/finalize macros
The lowercase macros are the core of the api for concrete testing and the calls to these macros shall end with a semicolon.

### Naming convention

For assertions of basic types, the convention is:

```
mcu_assert_[not\_]equal_\[type\]\[\_array\][\_message\]
```


## Extending minicutest

Minicutest has a default behavior fo verbosity, and how to log reports. One can change this behavior by defining two macros : 
	- CUSTOM_PRINT_METHOD
	- VERBOSITY_USER

Moreover, it is frequent that projects (such as embedded software projects for example) redefine base types of variables (to include the length of the variable e.g. ). It is then advised to encapsulate minicutest assert macros into user-defined macros.


These two problems can be solved using a custom header that includes minicutest, and that is then include into your unittests instead of minicutest.

```c
#include <minicutest.h>
#include <my_terrific_logger.h>

#define VERBOSITY_USER (0x01)  // To only have first level of verbosity

#define CUSTOM_PRINT_METHOD my_terrific_logger // Do not use printf for logging but custom logger

#define my_assert_equal_uint8 mcu_assert_equal_uchar // For 8-bit unsigned integer, use minicutest unsigned-char asserts
```
