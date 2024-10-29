#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pthread.h>

#define NOD_NAME "/dev/deviceFile"

int fd;


void* pwm(void* arg){
	int* num = (int*) arg;
	while(1){
		for(int i=0;i<100;i++){
			if(i==0) ioctl(fd, _IO(0,3), 0);
			if(i==*num) ioctl(fd, _IO(0,4), 0);
			sleep(0.01);
		}
	}
}

int main(){
    fd = open(NOD_NAME, O_RDWR);
    if( fd<0 ){
        printf("ERROR\n");
        exit(1);
    }

    int num;
 	pthread_t thread;

    // 스레드 생성
    if (pthread_create(&thread, NULL, pwm, &num) != 0) {
        fprintf(stderr, "스레드 생성 실패\n");
        return 1;
    }
	
    while(1){
        printf(">>");
        scanf("%d", &num);
        if( num < 10 || num > 90 ){
            printf("exit\n");
            break;
        }
    }
	pthread_cancel(thread);
    pthread_join(thread, NULL);
	ioctl(fd, _IO(0,4), 0);
	close(fd);
    return 0;
}
