// Final Project Milestone 3 - Product Class
// Product.h
// Date	2018-08-03
// Author	Sean Surjanto
// 148057177
#ifndef PRODUCT_AMA_H
#define PRODUCT_AMA_H
#include "ErrorState.h"
#include <iostream>
#include <cstring>
#include <fstream>

#define max_sku_length 7
#define max_unit_length 10
#define max_name_length 75
#define tax 0.13

namespace AMA {

	class Product {

	private:
		char productType;
		char productSku[max_sku_length + 1];
		char productUnit[max_unit_length + 1];
		char* productName;
		int qtyHold;
		int qtyNeed;
		double productPrice;
		bool taxStatus;
		ErrorState errorState;

	protected:
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double price() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;

	public:
		Product(char type = 'N');
		Product(const char*, const char*, const char*, int inHolding = 0, bool inTax = true, double inPrice = 0, int inNeed = 0);
		Product(const Product&);
		Product& operator=(const Product&);
		~Product();
		std::fstream& store(std::fstream&, bool newLine = true) const;
		std::fstream& load(std::fstream&);
		std::ostream& write(std::ostream&, bool) const;
		std::istream& read(std::istream&);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded()const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const Product&) const;
		int operator+=(int);
	};
	std::ostream& operator<<(std::ostream&, const Product&);
	std::istream& operator>>(std::istream&, Product&);
	double operator+=(double&, const Product&);
}
#endif 


