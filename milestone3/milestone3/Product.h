#ifndef MY_PRODUCT_H
#define MY_PRODUCT_H
#include "ErrorState.h"
#include <iostream>

namespace constants {
	const int sku = 7;
	const int unit = 10;
	const int user = 75;
	const double tax = 1.13;
}

namespace AMA {

	class Product {

		char productType;
		char productSku[constants::sku];
		char productUnit[constants::unit];
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
		Product();
		Product(char);
		Product(const char*, const char*, const char*, int, bool, double, int);
		Product(Product&);
		Product& operator*(Product&);
		~Product();
		std::fstream& store(std::fstream&, bool) const;
		std::fstream& load(std::fstream&);
		std::ostream& write(std::ostream&, bool) const;
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded()const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const Product&) const;
		int operator+=(int);
		friend std::ostream& operator<<(std::ostream&, const Product&);
		friend std::istream& operator>>(std::istream&, Product&);
		friend double operator+=(double&, const Product&);
	};
}
#endif // !MY_PRODUCT_H
