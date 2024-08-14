#ifndef DATE_H
#define DATE_H

#include "main.h"

namespace date{
class Date{
public:
    Date();
    Date(int n);
    Date(int day, int month, int year, int hour, int min, std::string am_pm);

    //get functions
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    std::string getDate() const;

    int getHour() const;
    int getMin() const;
    std::string getAm_Pm() const;
    std::string getTime() const;

    std::string getDate_Time() const;

    //set functions
    int setDay(int day);
    int setMonth(int Month);
    int setYear(int year);
    int setDate(std::string date);

    int setHour(int hour);
    int setMin(int min);
    int setAm_Pm(std::string am_pm);
    int setTime(std::string time);

    int setDate_Time(std::string date_time);

    //helper functions
    int setTodaysDate();
    int createDate();
    int createTime();
    int createDate_Time();
    void updateClass();

    //Overload operators
    bool operator>(Date& other) const;
    Date& operator=(Date& other);

    //Random functions to speed up the process to increment days.
    bool isLeapYear() const;
    int daysInMonth() const;
    int dayOfWeek() const;
    int addDays(int daysToAdd);

private:
    int day;
    int month;
    int year;
    std::string date;

    int hour;
    int min;
    std::string am_pm;
    std::string time;

    std::string date_time;

};
}
#endif
