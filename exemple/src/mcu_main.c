#include <stdio.h>

#define VERBOSITY_USER (0x01)
#include <minicutest.h>
#include <mcu_suite1.h>


int main() {

	TEST_SUITE_RUN(mcu_suite1);

	return(0);
}