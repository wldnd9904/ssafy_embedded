#include "common.h"
#include"partA.h"
#include"partB.h"

//#define RELEASE
#define DEBUG

#ifndef RELEASE
#include <stdio.h>
#endif

int main() {

	printf("pa = %d, pb = %d\n", pa, pb);
	partA();
	partB();
	printf("pa = %d, pb = %d\n", pa, pb);

	return 0;
}