// Final Project Milestone 4 - iProduct Interface
// iProduct.h
// Date	2018-08-03
// Author	Sean Surjanto
// 148057177

#ifndef I_PRODUCT_AMA_H
#define I_PRODUCT_AMA_H

#include <fstream>
#include <iostream>

namespace AMA{

	class iProduct {
	public: 
		virtual std::fstream& store(std::fstream&, bool newLine = true) const = 0;
		virtual std::fstream& load(std::fstream&) = 0;
		virtual std::ostream& write(std::ostream&, bool) const = 0;
		virtual std::istream& read(std::istream&) = 0;
		virtual bool operator==(const char*) const = 0;
		virtual double total_cost() const = 0;
		virtual const char* name() const = 0;
		virtual void quantity(int) = 0;
		virtual int qtyNeeded() const = 0;
		virtual int quantity() const = 0;
		virtual int operator+=(int) = 0;
		virtual bool operator>(const iProduct&) const = 0;
		virtual ~iProduct() {};
	};

	std::ostream& operator<<(std::ostream&, const iProduct&);
	std::istream& operator>>(std::istream&, iProduct&);
	double operator+=(double&, const iProduct&);
	iProduct* CreateProduct();
	iProduct* CreatePerishable();
}
#endif // !I_PRODUCT_AMA_H

