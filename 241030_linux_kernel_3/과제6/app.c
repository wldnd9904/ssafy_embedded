#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pthread.h>

#define NOD_NAME "/dev/deviceFile"

struct Node {
	int pinno;
	int period;
};

int fd;


void* pwm(void* arg){
	struct Node* node = (struct Node *) arg;
	int pinno = node->pinno;
	while(1){
		ioctl(fd, _IO(0,3), &pinno);
		printf("%d %d\n", pinno, node->period);
		sleep(node->period);
	}
}

int main(){
    fd = open(NOD_NAME, O_RDWR);
    if( fd<0 ){
        printf("ERROR\n");
        exit(1);
    }

	struct Node node1 = {20, 5};
	struct Node node2 = {21, 7};
 	pthread_t thread1, thread2;
    // 스레드 생성
    if (pthread_create(&thread1, NULL, pwm, &node1) != 0) {
        fprintf(stderr, "스레드 생성 실패\n");
        return 1;
    }
	
    // 스레드 생성
    if (pthread_create(&thread2, NULL, pwm, &node2) != 0) {
        fprintf(stderr, "스레드 생성 실패\n");
        return 1;
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
	close(fd);
    return 0;
}
