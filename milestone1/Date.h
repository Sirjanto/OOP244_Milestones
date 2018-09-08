// Final Project Milestone 1
//
// Version 1.0
// Date
// Author
// Description
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#ifndef AMA_DATE_H
#define AMA_DATE_H

#define NO_ERROR  0
#define CIN_FAILED  1
#define YEAR_ERROR  2
#define MON_ERROR  3
#define DAY_ERROR  4

#define  min_year  2000
#define max_year  2030

#include <iostream>



namespace AMA {

	class Date {

		int cYear;
		int cMonth;
		int cDay;
		int compare;
		int errorState;

		int mdays(int, int)const;
		void errCode(int);

	public:

		Date();
		Date(const int, const int, const int);

		bool operator==(const Date&) const;
		bool operator!=(const Date&) const;
		bool operator<(const Date&) const;
		bool operator>(const Date&) const;
		bool operator<=(const Date&) const;
		bool operator>=(const Date&) const;

		int errCode() const;
		bool bad() const;

		std::istream& read(std::istream&);
		std::ostream& write(std::ostream&) const;
	};
	std::istream& operator>>(std::istream&, Date&);
	std::ostream& operator<<(std::ostream&, const Date&);
}
#endif
