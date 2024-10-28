#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define NOD_NAME "/dev/g7"

struct Node {
	int a;
	int b;
	int c;
	int d;
};

int main(){
	int fd = open(NOD_NAME, O_RDWR);
	if(fd<0) {
		printf("ERROR\n");
		exit(1);
	}
	struct Node node;
	int sum;
	printf("input 4 number: ");
	scanf("%d %d %d %d", &node.a, &node.b, &node.c, &node.d);
	ioctl(fd, _IO(0,3), &node);
	ioctl(fd, _IO(0,4), &sum);
	printf("sum: %d\n", sum);
	for(int i=1; i<=sum; i++){
		printf("hifaker %d\n", i);
	}

	close(fd);
}
