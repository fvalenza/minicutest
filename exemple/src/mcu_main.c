#include <stdio.h>

#define VERBOSITY_USER (0x01)
#include <minicutest.h>
#include <mcu_suite1.h>


int main() {

	test_group_initialize(example_minicutest_ts_group);
	
	test_suite_run(mcu_suite1);

	test_group_finalize();
	
	return(0);
}