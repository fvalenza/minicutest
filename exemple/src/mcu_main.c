#include <stdio.h>

#define VERBOSITY_USER (0x01)
#include <minicutest.h>
#include <mcu_suite1.h>


int main() {

	TEST_GROUP_INITIALIZE(example_minicutest_ts_group);
	
	TEST_SUITE_RUN(mcu_suite1);

	TEST_GROUP_FINALIZE();
	
	return(0);
}