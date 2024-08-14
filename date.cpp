#include "date.h"

using namespace date;

Date::Date(){
    setTodaysDate();
}

Date::Date(int n) {
    setTodaysDate();
    addDays(n);
}

Date::Date(int day, int month, int year, int hour, int min, std::string am_pm) {
    this->day = day;
    this->month = month;
    this->year = year;
    this->hour = hour;
    this->min = min;
    this->am_pm = am_pm;
    updateClass();
}

//Get functions
int Date::getDay() const{
    return this->day;
}

int Date::getMonth() const{
    return this->month;
}

int Date::getYear() const{
    return this->year;
}

std::string Date::getDate() const{
    return this->date;
}

int Date::getHour() const{
    return this->hour;
}

int Date::getMin() const{
    return this->min;
}

std::string Date::getAm_Pm() const{
    return this->am_pm;
}

std::string Date::getTime() const{
    return this->time;
}

std::string Date::getDate_Time() const{
    return this->date_time;
}

//Set functions
int Date::setDay(int date) {
    this->date = date;
    return 0;
}

int Date::setMonth(int month) {
    this->month = month;
    return 0;
}

int Date::setYear(int year) {
    this->year = year;
    return 0;
}

int Date::setDate(std::string date) {
    this->date = date;
    return 0;
}

int Date::setHour(int hour){
    this->hour = hour;
    return 0;
}

int Date::setMin(int min){
    this->min = min;
    return 0;
}

int Date::setAm_Pm(std::string am_pm){
    this->am_pm = am_pm;
    return 0;
}

int Date::setTime(std::string time){
    this->time = time;
    return 0;
}

int Date::setDate_Time(std::string date_time){
    this->date_time = date_time;
    return 0;
}

//Helper functions
int Date::setTodaysDate() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    this->year = localTime->tm_year - 100; //tm_year returns the year starting from 1900, so 2024 is 124 - 100 = 24
    this->month = localTime->tm_mon + 1;
    this->day = localTime->tm_mday;
    this->hour = localTime->tm_hour;
    this->min = localTime->tm_min;

    std::string min = std::to_string(this->min);

    if (this->min < 10)
        min = "0" + min;


    //Sets the time to am or pm depending on the time of day.
    if (this->hour > 12) {
        this->hour = this->hour % 12;
        this->am_pm = "pm";
    }
    else
        this->am_pm = "am";

    this->time = std::to_string(this->hour) + ":" + min + this->am_pm;
    this->date = std::to_string(this->month) + "/" + std::to_string(this->day) + "/" + std::to_string(this->year);
    this->date_time = this->date + " " + this->time;
    return 0;
}

int Date::createDate() {
    this->date = std::to_string(this->month) + "/" + std::to_string(this->day) + "/" + std::to_string(this->year);
    return 0;
}

int Date::createTime() {
    this->time = std::to_string(this->hour) + ":" + std::to_string(this->min) + this->am_pm;
    return 0;
}

int Date::createDate_Time(){
    this->date_time = this->date + " " + this->time;
    return 0;
}

void Date::updateClass() {
    createDate();
    createTime();
    createDate_Time();
    return;
}

//Newer than
bool Date::operator>(Date& other) const{
    if (this->year == other.getYear()) {
        if (this->month == other.getMonth()) {
            if (this->day == other.getDay()) {
                if (this->am_pm == other.getAm_Pm()) {
                    if (this->hour == other.getHour()) {
                        if (this->min > other.getMin())
                            return true;
                    }
                    else if (this->hour > other.getHour())
                        return true;
                }
                else if (this->am_pm == "am" && other.getAm_Pm() == "pm")
                    return true;
            }
            else if(this->day > other.getDay())
                return true;
        }
        else if(this->month > other.getMonth())
            return true;
    }
    else if(this->year > other.getYear())
        return true;
    return false;
}

Date& Date::operator=(Date& other){
    this->day = other.getDay();
    this->month = other.getMonth();
    this->year = other.getYear();
    this->date = other.getDate();
    this->hour = other.getHour();
    this->min = other.getMin();
    this->time = other.getTime();
    this->am_pm = other.getAm_Pm();
    this->date_time = other.getDate_Time();

    return *this;
}

bool Date::isLeapYear() const{
    return(this->year % 4);
}

int Date::daysInMonth() const{
    if(this->month == 2)
        return isLeapYear() ? 29 : 28;
    else if(this->month == 4 || this->month == 6 || this->month == 9|| this->month == 11)
        return 30;
    else
        return 31;
}
//Returns the day of the week, where 0 = Sunday, 1 = Monday ... 6 = Saturday
int Date::dayOfWeek() const{
    int y = this->year, m = this->month, dayOfWeek;
    if(m < 3){
        m += 12;
        y -= 1;
    }

    dayOfWeek = (day + 2 * m + 3 * (m + 1) / 5 + y + y / 4) % 7;

    return dayOfWeek;
}

int Date::addDays(int daysToAdd) {
    int daysAdded = 0;
    while (daysAdded < daysToAdd) {
        this->day++;
        if (day > (daysInMonth())) {
            this->day = 1;
            this->month++;
            if (this->month > 12) {
                this->month = 1;
                this->year++;
            }
        }
        if (dayOfWeek() != 0) //Remmeber, 0 = Sunday
            daysAdded++;
    }
    updateClass();
    return 0;
}

