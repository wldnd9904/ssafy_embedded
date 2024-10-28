#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define NOD_NAME "/dev/g6"

int main(){
	int fd = open(NOD_NAME, O_RDWR);
	if(fd<0) {
		printf("ERROR\n");
		exit(1);
	}
	int cmd, arg;
	int isRunning = 1;
	while(isRunning){
		printf("command : 3~6, Age, birth, phone number\n");
		scanf("%d %d", &cmd, &arg);
		
		switch(cmd){
			case 3:
			case 4:
			case 5:
			case 6:
				ioctl(fd, _IO(0,cmd), arg);
				break;
			default:
				printf("command range error\n");
				isRunning = 0;
				break;
		}
	}
	close(fd);
}
