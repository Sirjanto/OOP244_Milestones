// Final Project Milestone 3 - Product Class
// Product.cpp
// Date	2018-08-03
// Author	Sean Surjanto
// 148057177

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Product.h"

using namespace std;

namespace AMA {
	
	// Protected Member Functions

	void Product::name(const char* inName) {

		if (inName != nullptr) {
			if (strlen(inName) > max_name_length) {
				productName = new char[max_name_length + 1];
				strncpy(productName, inName, max_name_length);
				productName[max_name_length] = '\0';
			}
			else {
				productName = new char[strlen(inName) + 1];
				strncpy(productName, inName, strlen(inName));
				productName[strlen(inName)] = '\0';
			}
		}
		else {
			productName = nullptr;
		}
	}

	const char* Product::name() const {
		if (productName == nullptr) {
			return nullptr;
		}
		else {
			return productName;
		}
	}

	const char* Product::sku() const {
		return productSku;
	}
	
	const char* Product::unit() const {
		return productUnit;
	}

	bool Product::taxed() const {
		return taxStatus;
	}
	
	double Product::price() const {
		return productPrice;
	}

	double Product::cost() const {
		if (taxStatus == true) {
			return productPrice * (1 + tax);
		}

		return productPrice;
	}
	
	void Product::message(const char* error) {
		errorState.message(error);
	}
	
	bool Product::isClear() const {
		return errorState.isClear();
	}
	
	// Constructors (Public)

	Product::Product(char type) {
		productType = type;
		productSku[0] = '\0';
		productUnit[0] = '\0';
		productName = nullptr;
		qtyHold = 0;
		qtyNeed = 0;
		productPrice = 0;
		taxStatus = false;
	}
	
	Product::Product(const char* inSku, const char* inName, const char* inUnit, int inHold, bool taxable, double inPrice, int inNeed) {
		
		name(inName);
		strncpy(productSku, inSku, strlen(inSku) + 1);
		productSku[strlen(inSku)] = '\0';
		strncpy(productUnit, inUnit, strlen(inUnit) + 1);
		productUnit[strlen(inUnit)] = '\0';
		qtyHold = inHold;
		qtyNeed = inNeed;
		productPrice = inPrice;
		taxStatus = taxable;
	}

	Product::Product(const Product& copy) {
		if (this != &copy) {
			*this = copy;
		}
	}

	// Public Member Functions

	Product& Product::operator= (const Product& copy) {
		if (this != &copy) {

			name(copy.productName);
			strncpy(productSku, copy.productSku, strlen(copy.productSku) + 1);
			productSku[strlen(copy.productSku)] = '\0';
			strncpy(productUnit, copy.productUnit, strlen(copy.productUnit) + 1);
			productUnit[strlen(copy.productUnit)] = '\0';
			qtyHold = copy.qtyHold;
			qtyNeed = copy.qtyNeed;
			productPrice = copy.productPrice;
			taxStatus = copy.taxStatus;
		}
		return *this;
	}

	// Destructor

	Product::~Product() {
		delete[] productName;
		productName = nullptr;
	}

	// Store | Load | Read | Write

	std::fstream& Product::store(std::fstream& file, bool newLine) const {
		file << productType << "," << productSku << "," << productName << "," << productUnit << "," << taxStatus << ","
			 << productPrice << ","<< qtyHold << "," << qtyNeed;

		if (newLine == true) {
			file << endl;
		}

		return file;
	}

	std::fstream& Product::load(std::fstream& file) {
		char tSku[max_sku_length + 1];
		char tName[max_name_length + 1];
		char tUnit[max_unit_length + 1];
		int tHold;
		int tNeed;
		bool tTaxStatus;
		double tPrice;

		if (file.is_open()) {
			file.getline(tSku, max_sku_length + 1, ',');
			file.getline(tName, max_name_length + 1, ',');
			file.getline(tUnit, max_unit_length + 1, ',');
			file >> tTaxStatus;
			file.ignore();
			file >> tPrice;
			file.ignore();
			file >> tHold;
			file.ignore();
			file >> tNeed;

			Product temp(tSku, tName, tUnit, tHold, tTaxStatus, tPrice, tNeed);
			*this = temp;
		}
		return file;
	}

	std::ostream& Product::write(std::ostream& os, bool linear) const {

		if (errorState.isClear()) {

			if (linear) {

				os.width(max_sku_length);
				os.setf(ios::left);
				os << sku() << "|";

				os.width(20);
				os << name() << "|";

				os.width(7);
				os.unsetf(ios::left);
				os.setf(ios::fixed);
				os.precision(2);
				os << cost() << "|";

				os.width(4);
				os << quantity() << "|";

				os.width(10);
				os.setf(ios::left);
				os << unit() << "|";

				os.unsetf(ios::left);
				os.width(4);
				os << qtyNeeded() << "|";
			}

			else {
				os << " Sku: " << sku() << endl;
				os << " Name (no spaces): " << name() << endl;
				os << " Price: " << price() << endl;
				os << " Price after tax: ";
					if (taxed()) {
						os << cost() << endl;
					}
					else {
						os << "N/A" << endl;
					}
				os << " Quantity on Hand: " << quantity() << " " << unit() << endl;
				os << " Quantity needed: " << qtyNeeded();
			}
		}

		else {
			cout << errorState.message();
		}

		return os;
	}

	std::istream& Product::read(std::istream& is) {
		char tSku[max_sku_length + 1];
		char tName[max_name_length + 1];
		char tUnit[max_unit_length + 1];
		char tTaxed;
		double tPrice;
		int tHold;
		int tNeed;
		bool tTaxStatus;

		cout << " Sku: ";
		is >> tSku;
		cout << " Name (no spaces): ";
		is >> tName;
		cout << " Unit: ";
		is >> tUnit;
		cout << " Taxed? (y/n): ";
		is >> tTaxed;
		if (tTaxed == 'Y' || tTaxed == 'y' || tTaxed == 'N' || tTaxed == 'n') {
			if (tTaxed == 'Y' || tTaxed == 'y') {
				tTaxStatus = true;
			}
			else if (tTaxed == 'N' || tTaxed == 'n') {
				tTaxStatus = false;
			}

			cout << " Price: ";
			is >> tPrice;

			if (is.fail()) {
				errorState.message("Invalid Price Entry");
			}
			else {
				cout << " Quantity on hand: ";
				is >> tHold;
				if (is.fail()) {
					errorState.message("Invalid Quantity Entry");
				}
				else {
					cout << " Quantity needed: ";
					is >> tNeed;

					if (is.fail()) {
						errorState.message("Invalid Quantity Needed Entry");
					}
					else {
						errorState.clear();
					}
					is.ignore(); // temp fix
				}
			}

		}
		else {
			errorState.message("Only (Y)es or (N)o are acceptable");
			is.clear();
			is.setstate(std::ios::failbit);
		}

		Product temp(tSku, tName, tUnit, tHold, tTaxStatus, tPrice, tNeed);
		*this = temp;

		return is;
	}
	
	// Public Member Functions

	bool Product::operator==(const char* inSku) const {
		if (strcmp(productSku, inSku) == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	
	double Product::total_cost() const {
		return qtyHold * cost();
	}
	
	void Product::quantity(int inHold) {
		qtyHold = inHold;
	}
	
	bool Product::isEmpty() const {
		if (productSku[0] == '\0'  && productName == nullptr && productUnit[0] == '\0') {
			return true;
		}
		else {
			return false;
		}		
	}
	
	int Product::qtyNeeded() const {
		return qtyNeed;
	}
	
	int Product::quantity() const {
		return qtyHold;
	}

	bool Product::operator>(const char* inSku) const {
		if (strcmp(productSku, inSku) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Product::operator>(const iProduct& rhs) const {
		if (strcmp(productName, rhs.name()) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	int Product::operator+=(int add) {
		if (add > 0) {
			qtyHold += add;
		}
			return qtyHold;
	}

	// Helper Functions
	
	std::ostream& operator<<(std::ostream& os, const iProduct& obj) {
		obj.write(os, true);
		return os;
	}
	
	std::istream& operator>>(std::istream& is, iProduct& obj) {
		obj.read(is);
		return is;
	}
	
	double operator+=(double& added, const iProduct& obj) {
		added += obj.total_cost();
		return added;
	}
}
