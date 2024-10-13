#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main(){
	
    while (1) {
        struct timeval time;
	    gettimeofday(&time, NULL);

        struct tm *localt = localtime(&time);

		int year = 1900 + localt->tm_year;
		int month = 1 + localt->tm_mon;
		int date = localt->tm_mday;
		int hour = localt->tm_hour;
		int minute = localt->tm_min;
		int second = localt->tm_sec;
		int usec = time.tv_usec % 1000000;

        printf("%04d-%02d-%02d ", year, month, date);
	    printf("%02d:%02d:%02d.%06d\n", hour, minute, second, usec);
    }
    
	return 0;
}
