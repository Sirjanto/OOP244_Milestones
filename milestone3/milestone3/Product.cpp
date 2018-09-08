#include "Product.h"
#include <iostream>
#include <cstring>
using namespace std;

namespace AMA {

	void Product::name(const char* inName) {

		delete[] productName;
		
		if (inName != nullptr) {
			productName = new char[strlen(inName + 1)];
			strncpy(productName, inName, strlen(inName));
			productName[(strlen(inName)+1)] = '\0';
		}
		else {
			productName = nullptr;
		}
	}

	const char* Product::name() const {
		return productName;
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
		if (taxed()) {
			return productPrice * constants::tax;
		}
		else {
			productPrice;
		}	
	}

	void Product::message(const char* error) {
		errorState.message(error);
	}

	bool Product::isClear() const {
		if (errorState.isClear()) {
			return true;
		}

		else {
			return false;
		}
	}
	
	Product::Product() {
		productType = 'N';
	}

	Product::Product(char type) {
		productType = type;
	}

	Product::Product(const char* inSku, const char* inName, const char* inUnit, int inHolding, bool inTax, double inPrice, int inNeed) {
		if (inSku != nullptr || inName != nullptr) {
			strncpy(productSku, inSku, constants::sku);
			productSku[constants::sku] = '\0';
			name(inName);
			strncpy(productUnit, inUnit, constants::unit);
			productUnit[constants::unit] = '\0';
			qtyNeed = inNeed;
			qtyHold = inHolding;
			taxStatus = inTax;
			productPrice = inPrice;
		}
		else {
			productSku[0] = '\0';
			name(inName);
			productUnit[0] = '\0';
			qtyNeed = 0;
			qtyHold = 0;
			taxStatus = true;
			productPrice = 0;
		}
	}

	Product::Product(Product& copy) {
		*this = copy;
	}

	Product& Product::operator*(Product& copy) {
		*this = copy;
	}



}