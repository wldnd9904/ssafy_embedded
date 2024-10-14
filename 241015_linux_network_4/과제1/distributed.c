#include <stdio.h>
#include <pthread.h>

char arr[4][4]={
	"A",
	"B",
	"C",
	"D"
};

void* run(void* arg){
	int line = *(int*) arg;
	for(int i=0; i<4; i++) arr[line][i] += 32;
	return 0;
}

int main(){
	pthread_t tid[4];
	int id[4];

	for(int i=0; i<4; i++){
		id[i] = i;
		pthread_create(&tid[i], NULL, run, &id[i]);
	}
	for(int i=0; i<4; i++) pthread_join(tid[i], NULL);
	
	for(int y=0; y<4; y++){
		printf("%c\n", arr[y][0]);
	}
	return 0;
}
