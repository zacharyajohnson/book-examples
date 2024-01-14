static char daytab[2][13] = {
        { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
        int i, leap;

        if (year < 0) {
                return -1;
        } else if (month < 1 || month > 12) {
               return -1;
        } else if (day < 1 || month > 31) {
               return -1;
        } 

        leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
        for (i = 1; i < month; i++)
                day += daytab[leap][i];
        return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
        int i, leap;

        if (year < -1) {
                *pmonth = -1;
                *pday = -1;
                return;
        } else if (yearday < 1 || yearday > 365) {
                *pmonth = -1;
                *pday = -1;
                return;
        }

        leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
        for (i = 1; yearday > daytab[leap][i]; i++)
                yearday -= daytab[leap][i];
        *pmonth = i;
        *pday = yearday;
}
