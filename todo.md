TODOLIST
---
- Fix warnings -Wformats and -Wformat_security ?
- User defined macros for int16, int32 etc... as it is platform dependent. Shall be a custom .h file that includes minicutest.h ? + define VERBOSITY / LOG_FUNCTION, etc  
- Check Naming_convention : MCU_ASSERT_EQUAL_[TYPE][SIZE][_ARRAY][_BASE]
- Examples au propre
- Cleaning minicutest une fois tout fini. Check naming_convention + semicolon (lower/upper case)
- Readme
- Push


# 	macro that must end with semicolon shall be lowercasae.
# 	macro that dont need semicolon shall be uppercase.
# 	internal macro shall be ??? upper or lower ?? with __MACRO__ ???


Potential improvments
---
- Rework verbosity ? (Different levels : each index of array, for each test in test cases, and test_group_overview )
- Add boolean ? With user defined boolean macros ??
- For arrays, add with verrbosity the prrint of each line that failed ? Too verbose no  ? If I add it, it should be something like this:
	
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







