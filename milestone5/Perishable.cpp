// Final Project Milestone 5 - Perishables
// Perishable.cpp
// Date	2018-08-08
// Author	Sean Surjanto
// 148057177

#include "Perishable.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <string>

using namespace std;

namespace AMA {

	// Default constructor, sets type to P as default
	Perishable::Perishable() : Product::Product('P') {
		_expiry = Date();
	}
	
	// stores from a file 
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
		Product::store(file, false);			// use existing store member function from Product Base Class
		file << "," << _expiry;				// store expiry date 
		if (newLine) {
			file << endl;
		}
		return file;
	}
	
	// loads from a file
	std::fstream& Perishable::load(std::fstream& file) {
		Product::load(file);				// use existing load member function from Product Base Class
		file.ignore();					
		_expiry.read(file);				// loads expiry date

		return file;
	}
	
	// outputs product information including expiry date
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		os << setfill(' ');
		if (Product::write(os, linear)) {		// use existing write member function from Product Base Class
			if (Product::isClear()) {		// outputs expiry date info according to specified format		
				if (linear) {
					os << _expiry;
				}
				else {
					os << endl << " Expiry date: " << _expiry;
				}
			}
		}
		return os;
	}

	std::istream& Perishable::read(std::istream& is) {
		Date tempExp;					// create a temp object to check everything is valid first 

		Product::read(is);				// use existing read function for all product related data
		if (!is.fail()) {				// if successful then also add the expiry date information
			cout << " Expiry date (YYYY/MM/DD): ";
			is >> tempExp;
			if (tempExp.errCode() != 0) {			// output proper error message if needed
				is.setstate(std::ios::failbit);
				switch (tempExp.errCode()) {
				case CIN_FAILED:
					Product::message("Invalid Date Entry");
					break;
				case YEAR_ERROR:
					Product::message("Invalid Year in Date Entry");
					break;
				case MON_ERROR:
					Product::message("Invalid Month in Date Entry");
					break;
				case DAY_ERROR:
					Product::message("Invalid Day in Date Entry");
					break;
				default:
					break;
				}
			}
		}
		_expiry = tempExp;
		return is;
	}


	const Date& Perishable::expiry() const {
		return _expiry;
	}
}

