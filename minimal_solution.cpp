#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
class Date
{
public:
    int _year;
    int _month;
    int _day;
    
    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    
    int getDaysInMonth(int year, int month) const {
        if (month == 2 && isLeapYear(year)) {
            return 29;
        }
        return month_days[month];
    }
    
    bool isValidDate(int year, int month, int day) const {
        if (year < 1900 || year > 2030) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > getDaysInMonth(year, month)) return false;
        return true;
    }
    
    long toDays() const {
        long totalDays = 0;
        
        for (int y = 1900; y < _year; y++) {
            totalDays += isLeapYear(y) ? 366 : 365;
        }
        
        for (int m = 1; m < _month; m++) {
            totalDays += getDaysInMonth(_year, m);
        }
        
        totalDays += _day - 1;
        
        return totalDays;
    }
    
    void fromDays(long days) {
        _year = 1900;
        _month = 1;
        _day = 1;
        
        while (days >= 365) {
            int daysInYear = isLeapYear(_year) ? 366 : 365;
            if (days < daysInYear) break;
            days -= daysInYear;
            _year++;
        }
        
        for (int m = 1; m <= 12; m++) {
            int daysInMonth = getDaysInMonth(_year, m);
            if (days < daysInMonth) {
                _month = m;
                break;
            }
            days -= daysInMonth;
        }
        
        _day = days + 1;
    }

    Date() : _year(1900), _month(1), _day(1) {}
    
    Date(int yy, int mm, int dd) {
        if (isValidDate(yy, mm, dd)) {
            _year = yy;
            _month = mm;
            _day = dd;
        } else {
            _year = 1900;
            _month = 1;
            _day = 1;
        }
    }
    
    Date& operator++() {
        _day++;
        if (_day > getDaysInMonth(_year, _month)) {
            _day = 1;
            _month++;
            if (_month > 12) {
                _month = 1;
                _year++;
            }
        }
        return *this;
    }
    
    Date operator++(int) {
        Date temp = *this;
        ++(*this);
        return temp;
    }
    
    Date& operator--() {
        _day--;
        if (_day < 1) {
            _month--;
            if (_month < 1) {
                _month = 12;
                _year--;
            }
            _day = getDaysInMonth(_year, _month);
        }
        return *this;
    }
    
    Date operator--(int) {
        Date temp = *this;
        --(*this);
        return temp;
    }
    
    Date operator+(int days) const {
        Date result = *this;
        long totalDays = result.toDays() + days;
        result.fromDays(totalDays);
        return result;
    }
    
    Date operator-(int days) const {
        Date result = *this;
        long totalDays = result.toDays() - days;
        result.fromDays(totalDays);
        return result;
    }
    
    long operator-(const Date& other) const {
        long diff = this->toDays() - other.toDays();
        return diff < 0 ? -diff : diff;
    }
    
    int operator<(const Date& other) const {
        if (_year != other._year) return _year < other._year;
        if (_month != other._month) return _month < other._month;
        return _day < other._day;
    }
    
    void out() const {
        cout << _year << "-" << _month << "-" << _day << endl;
    }
};

ostream& operator<<(ostream& os, const Date& date) {
    os << date._year << "-" << date._month << "-" << date._day;
    return os;
}

void Test()
{
    int op;
    cin >> op;
    int yy, mm, dd;
    if (op == 1 || op == 0)
    {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
    }
    if (op == 2 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << endl;
        for (int i=0;i<5;++i) cout << d0++ << endl;
        for (int i=0;i<5;++i) cout << d0-- << endl;
        for (int i=0;i<2;++i) cout << --d0 << endl;
        cout << d0 << endl;
    }
    if (op == 3 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        cout << d0 - 1000 << endl;
    }
    if (op == 4 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}

int main()
{
    Test();
    return 0;
}