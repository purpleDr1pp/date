#include <tuple>

class Date {
private:
	int d = 0;
	
	int GetDaysInYear(int year) const {
		return 337 + GetDaysInFeb(year);
	}

	int GetDaysInFeb(int year) const {
		if ((!(year % 4) && (year % 100)) || !(year % 400)) {
			return 29;
		}
		return 28;
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

	void SetDays(int day, int month, int year) {
		d = 0;
		for (int i = 1970; i < year; ++i) {
			d += GetDaysInYear(i);
		}
		d = d + DaysPassedToMonth(month, year) + day;
	}

	std::tuple<int, int, int> SetDateFromDays() const{
		int days = d;
		int m = 1;
		int y = 1970;

		while (days > GetDaysInYear(y)) {  
			days -= GetDaysInYear(y);
			++y;
		}

		/*while (days > GetDaysInMonth(m, y)) {
			days -= GetDaysInMonth(m, y);
			++m;
		} */

		while (days > DaysPassedToMonth(m + 1, y)) {  
			++m;
		}

		int day = days - DaysPassedToMonth(m, y);

		return { day, m, y };
	}

	int GetDays() const  {
		return d;
	}

	void SetFromDays(int inp_days)  {
		d = inp_days;
	}


public:
	Date(int day, int month, int year) {
		if (month > 12 || month < 1 || day > GetDaysInMonth(month, year) || day < 1) {
			d = 0;
		}
		else {
			SetDays(day, month, year);
		}
	}


	int GetDay() const {
		return std::get<0>(SetDateFromDays());
	}

	int GetMonth() const {
		return std::get<1>(SetDateFromDays());
	}

	int GetYear() const {
		return std::get<2>(SetDateFromDays());
	}

	Date operator + (int k) const {
		Date result(*this);
		result.SetFromDays(result.GetDays() + k);
		return result;
	}

	Date operator - (int k) const {
		Date result(*this);
		result.SetFromDays(result.GetDays() - k);
		return result;
	}

	int operator - (const Date& other) const {
		return GetDays() - other.GetDays();
	}

};




