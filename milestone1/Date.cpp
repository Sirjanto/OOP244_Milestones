// Final Project Milestone 1
//
// Version 1.0
// Date: July 13, 2018
// Author: Sean Kevin Surjanto
// Description
//
// Date.cpp file for milestone 1
//
//
// Revision History
// -----------------------------------------------------------
// N/A
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include "Date.h"

using namespace std;

namespace AMA {

	// number of days in month mon_ and year year_
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	// set error state as the inputted error code
	void Date::errCode(int errorCode) {
		errorState = errorCode;
	}

	// sets the date variables to an empty safe state
	Date::Date() {
		cYear = 0;
		cMonth = 0;
		cDay = 0;
		compare = 0;
		errorState = NO_ERROR;
	}

	// sets year, month, and day inputted if inputs are valid
	Date::Date(const int yy, const int mm, const int dd) {
		
		errorState = NO_ERROR;

		// check that year is valid and if not set as safe empty state with a year error
		if (yy >= min_year && yy <= max_year) {
			cYear = yy;
		}
		else {
			*this = Date();
			errorState = YEAR_ERROR;
		}

		// check that month is valid and if not set as safe empty state with a month error
		if (mm > 0 && mm < 13 && errorState == NO_ERROR) {
			cMonth = mm;
		}
		else {
			*this = Date();
			errorState = MON_ERROR;
		}

		// check that day is valid and if not set as safe empty state with a day error
		if (dd > 0 && dd < mdays(mm,yy) && errorState == NO_ERROR) {
			cDay = dd;
		}
		else {
			*this = Date();
			errorState = DAY_ERROR;
		}

		// sets compare value
		compare = yy * 372 + mm * 13 + dd;
	}
	
	// operator to check if dates are the same
	bool Date::operator==(const Date& rhs) const {

			if (rhs.cYear == cYear && rhs.cMonth == cMonth && rhs.cDay == cDay) {
				return true;
			}
			else {
				return false;
			}
	}

	// operator to check if date is not the same
	bool Date::operator!=(const Date& rhs) const {

			if (rhs.cYear != cYear || rhs.cMonth != cMonth || rhs.cDay != cDay) {
				return true;
			}
			else {
				return false;
			}
	}

	// operator to check if left hand side date is less than right hand side date
	bool Date::operator<(const Date& rhs) const {

			if (cYear < rhs.cYear) {
				return true;
			}
			else if (rhs.cYear == cYear && cMonth < rhs.cMonth) {
				return true;
			}
			else if (rhs.cYear == cYear && rhs.cMonth == cMonth && cDay < rhs.cDay) {
				return true;
			}
			else {
				return false;
			}
	}

	// operator to check if left hand side date is greater than right hand side date
	bool Date::operator>(const Date& rhs) const {
		if (cYear > rhs.cYear) {
			return true;
		}
		else if (rhs.cYear == cYear && cMonth > rhs.cMonth) {
			return true;
		}
		else if (rhs.cYear == cYear && rhs.cMonth == cMonth && cDay > rhs.cDay) {
			return true;
		}
		else {
			return false;
		}
	}

	// operator to check if left hand side date is less than or equal to right hand side date
	bool Date::operator<=(const Date& rhs) const {
		if (cYear <= rhs.cYear) {
			return true;
		}
		else if (rhs.cYear == cYear && cMonth <= rhs.cMonth) {
			return true;
		}
		else if (rhs.cYear == cYear && rhs.cMonth == cMonth && cDay <= rhs.cDay) {
			return true;
		}
		else {
			return false;
		}
	}

	// operator to check if left hand side date is greater than or equal to right hand side date
	bool Date::operator>=(const Date& rhs) const {
		if (cYear >= rhs.cYear) {
			return true;
		}
		else if (rhs.cYear == cYear && cMonth >= rhs.cMonth) {
			return true;
		}
		else if (rhs.cYear == cYear && rhs.cMonth == cMonth && cDay >= rhs.cDay) {
			return true;
		}
		else {
			return false;
		}
	}

	// checks the error state
	int Date::errCode() const {
		return errorState;
	}

	// bad date if error state is not 0
	bool Date::bad() const {
		if (errorState != 0) {
			return true;
		}
		else {
			return false;
		}
	}
	
	// redefine read function to read date format
	std::istream& Date::read(std::istream& istr) {
		
		char slash = '/';
		istr.clear();

		istr >> cYear >> slash >> cMonth >> slash >> cDay;

		if (istr.fail()) {
			*this = Date();
			errCode(CIN_FAILED);
		}
		else if (cYear < min_year || cYear > max_year) {
			*this = Date();
			errCode(YEAR_ERROR);
		}
		else if (cMonth < 1 || cMonth > 12) {
			*this = Date();
			errCode(MON_ERROR);
		}
		else if (cDay > mdays(cMonth,cYear) || cDay < 1) {
			*this = Date();
			errCode(DAY_ERROR);
		}
		
		return istr;
	}

	// redefine write function to output date in proper format
	std::ostream& Date::write(std::ostream& ostr) const {
			
		if (!bad()) {

			ostr << setw(1) << setfill('0') << cYear << '/'
				 << setw(2) << setfill('0') << cMonth << '/'
				 << setw(2) << setfill('0') << cDay;

			return ostr;
		}

		else {
			ostr << "0/00/00";
			return ostr;
		}
	}

	// redefine input operator to read date format
	std::istream& operator >> (std::istream& istr, Date& date){

		date.read(istr);
		return istr;
	}

	// redefine output operator to output date in proper format
	std::ostream& operator << (std::ostream& ostr, const Date& date){

		date.write(ostr);
		return ostr;
	}
}
