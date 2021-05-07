#ifndef MCU_SUITE1_H
#define MCU_SUITE1_H

#include <minicutest.h>

typedef struct
{
	int a;
	int b;
} point2D;


external_declare_test_suite(mcu_suite1);

#endif // MCU_SUITE1_H