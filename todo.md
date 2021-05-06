TODOLISt
---

- Add before/after test_case functions ?? Or let user do it ?
- Rework verbosity ?
- Add boolean ? With user defined boolean macros ??

- Naming_convention : MCU_ASSERT_EQUAL_[TYPE][SIZE][_ARRAY][_BASE]
- Add exemples



// User defined macros for int16, int32 etc... as it is platform dependent. Shall be a custom .h file that includes minicutest.h. 


TODO URGENT
// add array base types( 1 ERROR for report but count number of fails in forloop ? need static global counters) --> Assertion failed : toto == titi : x fails over y values
// add array custom_cmp
// Examples au propre
// Cleaning minicutest une fois tout fini. Check naming_convention + semicolon (lower/upper case)
// Readme
// Push
// add color in reporting ?




# 	macro that must end with semicolon shall be lowercasae.
# 	macro that dont need semicolon shall be uppercase.
# 	internal macro shall be ??? upper or lower ?? with __MACRO__ ???