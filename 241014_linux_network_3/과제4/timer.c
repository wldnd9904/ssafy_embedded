#include <stdio.h>
#include <time.h>
#include <unistd.h>

char *days[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

int main(){
    while (1) {
        time_t t = time(0);
        struct tm *localt = localtime(&t);
		int year = 1900 + localt->tm_year;
		int month = 1 + localt->tm_mon;
		int date = localt->tm_mday;
		int day = localt->tm_wday;
		int hour = localt->tm_hour;
		int minute = localt->tm_min;
		int second = localt->tm_sec;


        printf("%04d/%02d/%02d %s\n%02d : %02d : %02d\n", year, month, date, days[day], hour, minute, second);
        sleep(1);
    }
    return 0;
}
