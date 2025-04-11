// Counting Sundays

#include <stdio.h>

#define TARGET_CENTURY 20

int is_leap(int year)
{
    return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int main(void)
{
    int mdays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,};
    
    int wday_num = (1 + (is_leap((TARGET_CENTURY - 1) * 100)) ? 366 : 365) % 7;
    int count = 0;

    for (int year = (TARGET_CENTURY - 1) * 100 + 1; year <= TARGET_CENTURY * 100; year++) {
        mdays[2] = is_leap(year) ? 29 : 28;

        for (int month = 1; month <= 12; month++) {
            if (wday_num == 0) {
                count++;
            }
            wday_num = (wday_num + mdays[month]) % 7;
        }
    }

    printf("%d\n", count);

    return 0;
}
