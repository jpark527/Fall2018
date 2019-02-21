#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MONTH 0
#define DAY 1
#define YEAR 2
#define NUM_OF_MONTH 12

typedef bool (*isDateValid)(int *);

void initialize(isDateValid *validator, char **dayOfWeek);
bool day30(int *date);
bool day31(int *date);
bool isLeapyear(int *date);
bool february(int *date);
bool isNumber(const char *s);
bool isValid(char *argv, int *date, isDateValid *validator);
void initDoomsday(int *date, int *doomsday);
int getDoomsday(int *date, int *doomsday);


int main(int argc, char **argv) {
    isDateValid *validator = malloc(sizeof(isDateValid)*NUM_OF_MONTH);
    char **dayOfWeek = malloc(sizeof(char*)*7);
    int *date = malloc(sizeof(int)*3), *doomsday = malloc(sizeof(int)*NUM_OF_MONTH);
    initialize(validator, dayOfWeek);
    if(argc-2 || !isValid(*(argv+1), date, validator))
        puts("usage: day [mm-dd-yyyy]");
    else {
        initDoomsday(date, doomsday);
        puts(dayOfWeek[getDoomsday(date, doomsday)]);
    }

    free(date), free(validator), free(doomsday), free(dayOfWeek);

    return 0;
}

void initialize(isDateValid *validator, char **dayOfWeek) {
    validator[0] = day31;
    validator[1] = february;
    validator[2] = day31;
    validator[3] = day30;
    validator[4] = day31;
    validator[5] = day30;
    validator[6] = day31;
    validator[7] = day31;
    validator[8] = day30;
    validator[9] = day31;
    validator[10] = day30;
    validator[11] = day31;
    dayOfWeek[0] = "Sunday";
    dayOfWeek[1] = "Monday";
    dayOfWeek[2] = "Tuesday";
    dayOfWeek[3] = "Wednesday";
    dayOfWeek[4] = "Thursday";
    dayOfWeek[5] = "Friday";
    dayOfWeek[6] = "Saturday";
}

bool day30(int *date) {
    return 0 < date[DAY] && date[DAY] < 31 && 0 <= date[YEAR]; 
}

bool day31(int *date) {
    return 0 < date[DAY] && date[DAY] < 32 && 0 <= date[YEAR]; 
}

bool isLeapyear(int *date) {
    return !(date[YEAR] & 3) && ((date[YEAR] % 25) || !(date[YEAR] & 15));
}

bool february(int *date) {
    return isLeapyear(date) ? 
        0 < date[DAY] && date[DAY] < 30 && 0 <= date[YEAR]
            :
        0 < date[DAY] && date[DAY] < 29 && 0 <= date[YEAR];
}

bool isNumber(const char *s) {
    while(*s) {
        if('0' > *s || *s > '9')
            return false;
        ++s;
    }
    return true;         
}

bool isValid(char *argv, int *date, isDateValid *validator) {
    char *splt = strtok(argv, "-");
    for(int i=0; splt && i<3; ++i) {
        if(!isNumber(splt))
            return false;
        else
            date[i]=atoi(splt);
        splt = strtok(NULL, "-");
    }
    return date[MONTH] > 0 && date[MONTH] < 13 && validator[date[MONTH]-1](date);
}

void initDoomsday(int *date, int *doomsday) {
    doomsday[0] = isLeapyear(date) ? 4 : 3;
    doomsday[1] = isLeapyear(date) ? 29 : 28;
    doomsday[2] = 0;
    doomsday[3] = 4;
    doomsday[4] = 9;
    doomsday[5] = 6;
    doomsday[6] = 11;
    doomsday[7] = 8;
    doomsday[8] = 5;
    doomsday[9] = 10;
    doomsday[10] = 7;
    doomsday[11] = 12;
}

int getDoomsday(int *date, int *doomsday) {
    int first2 = (int)(date[YEAR]/100), last2 = date[YEAR]%100, anchorday = 5*(first2%4)%7+2,
        dayOfWeek = ((int)(last2/12) + last2%12 + (int)((last2%12)/4))%7 + anchorday;
    return (700 + date[DAY] - doomsday[date[MONTH]-1] + dayOfWeek) % 7;
}

