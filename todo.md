TODOLIST
---

- Fix warnings -Wformats and -Wformat_security ?




Potential improvments
---

- Missing exhaustive list of all assert types with \_message.
- Rework verbosity ? (Different levels : each index of array, for each test in test cases, and test_group_overview ). Each level of verbosity shall be macro at the very begining of minicutest and then #define VERBOSITY_USER (VERBOSITY_LVL_1 | VERBOSITY_LVL_2) etc...
- Add boolean ? With user defined boolean macros ??
- For arrays, add with verbosity the print of each line that failed ? Too verbose maybe  ? If I add it, it should be something like this.

```
	#define MCU_ASSERT_EQUAL_TYPE_ARRAY_BASE(type, data, expected, expr, size) \
    	do \
    	{ \
            *nb_tests+=1;  \
        	nb_array_tests_failed = 0; \
        	char array_failed_tests[1000] = ""; \
        	int aft_next_snprintf = 0; \
        	for (size_t idx = 0; idx < size; ++idx) \
        	{ \
            	if (expr) \
            	{ \
                	++nb_array_tests_failed; \
                	aft_next_snprintf += snprintf(array_failed_tests+aft_next_snprintf, MAG "Expected " #type " , obtained " #type RESET "\n", expected, data) \\ // With #type depending on char, int, uint, etc..
            	} \
        	} \
        	if (nb_array_tests_failed > 0) \
        	{ \
                *nb_failed+=1; \
            	char array_test_results[1024]; \
            	int s = sprintf(array_test_results,  "\""#data" == "#expected"\" : " MAG "%u ko / %u " RESET , nb_array_tests_failed, size); \
            	MCU_LOG_BASE(__FILENAME__, test_suite, __func__, __LINE__, array_test_results);  \
        	} \
    	} while(0)
```

- In case i want to factorize in one macro the default messages. Do something like this. Warning : Problem when putting NULL as expected.

```
	#define STR_VALUE(arg) #arg

	#define DFAULT_EQUL_FAIL_MSG(data, expected) \\""#data" == "#expected"\\"
	#define DFAULT_NOT_EQUL_FAIL_MSG(data, expected) \\""#data" != "#expected"\\"

	#define toto(data, expected) #data " == " #expected
	MCU_ASSERT_BASE(test_suite, __func__, (data == expected), "\"" STR_VALUE(data) " == "#expected "\""); 

```