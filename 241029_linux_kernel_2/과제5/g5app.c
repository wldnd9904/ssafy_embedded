#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define NOD_NAME "/dev/g5"

int main(){
	int fd = open(NOD_NAME, O_RDWR);
	if(fd<0) {
		printf("ERROR\n");
		exit(1);
	}
	close(fd);
}
