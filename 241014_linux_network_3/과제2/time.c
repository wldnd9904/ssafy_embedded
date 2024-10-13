#include <stdio.h>
#include <sys/time.h>

int main(){
	struct timeval time;

	gettimeofday(&time, NULL);

	printf("sec : %ld\n", time.tv_sec);
	printf("usec : %ld\n", time.tv_usec);
	return 0;
}
