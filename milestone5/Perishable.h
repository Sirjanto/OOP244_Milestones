// Final Project Milestone 5 - Perishables
// Perishable.h
// Date	2018-08-08
// Author	Sean Surjanto
// 148057177

#ifndef PERISHABLE_AMA_H
#define PERISHABLE_AMA_H
#include "Product.h"
#include "Date.h"
#include <fstream>
#include <iostream>

namespace AMA {
	class Perishable : public Product {
	private:
		Date _expiry;
	public:
		Perishable();
		std::fstream& store(std::fstream&, bool newLine = true) const;
		std::fstream& load(std::fstream&);
		std::ostream& write(std::ostream&, bool) const;
		std::istream& read(std::istream&);
		const Date& expiry() const;
	};
}
#endif // !1
