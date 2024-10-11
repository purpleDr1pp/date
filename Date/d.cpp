#include <iostream>

class Date {
private:
	int d = 1;
	int m = 1;
	int y = 1970;

	int GetDaysInFeb(int year) const {
		if ((!(year % 4) && (year % 100)) || !(year % 400)) {
			return 29;
		}
		else {
			return 28;
		}

	}

	int GetDaysInYear(int year) const {
		return 337 + GetDaysInFeb(year);
	}

	int GetDaysInMonth(int month, int year) const {
		switch (month) {
		case 2:
			return GetDaysInFeb(year);
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		default:
			return 30;
		}
	}

	int DaysPassedToMonth(int month, int year) const {
		int days = 0;
		for (int i = 1; i < month; ++i) {
			days += GetDaysInMonth(i, year);
		}
		return days;
	}

	bool IsCorrectDate() const {
		return GetMonth() <= 12 && GetMonth() >= 1 && GetDay() <= GetDaysInMonth(GetMonth(), GetYear()) && GetDay() > 0;
	}

	int GetDays() const {
		int days = 0;
		for (int cntY = 1970; cntY < GetYear(); ++cntY) {
			days += GetDaysInYear(cntY);
		}
		return days + DaysPassedToMonth(GetMonth(), GetYear()) + GetDay();
	}

	void SetDateFromDays(int days) {
		y = 1970;
		m = 1;
		while (days >= GetDaysInYear(GetYear())) {
			days -= GetDaysInYear(GetYear());
			++y;
		}
		while (days >= GetDaysInMonth(GetMonth(), GetYear())) {
			days -= GetDaysInMonth(GetMonth(), GetYear());
			++m;
		}
		d = days;	
	}
	
public:
	Date(int day, int month, int year)
		: d{ day }, m{ month }, y{ year } {
		if (!IsCorrectDate()) {
			d = 1;
			m = 1;
			y = 1970;
		}
	}

	
	int GetDay() const {
		return d;
	}
	int GetMonth() const {
		return m;
	}
	int GetYear() const {
		return y;
	}

	Date operator + (int k) const{
		Date result(*this);
		result.SetDateFromDays(result.GetDays() + k);
		return result;
	}
	Date operator - (int k) const {
		Date result(*this);
		result.SetDateFromDays(result.GetDays() - k);
		return result;
	}
	
	int operator - (const Date& other) const {
		return GetDays() - other.GetDays();
	}
	
};


