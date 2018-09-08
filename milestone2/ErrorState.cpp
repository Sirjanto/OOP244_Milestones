// Final Project Milestone 2 - ErrorState Class
// ErrorState.h
// Date	2018-07-19
// Author	Sean Surjanto

#include <iostream>
#include <cstring>
#include "ErrorState.h"

#define _CRT_SECURE_NO_WARNINGS

namespace AMA {
	
	// sets a safe empty state
	ErrorState::ErrorState() {
		error = nullptr;
	}

	// sets error message as specified if message exist
	ErrorState::ErrorState(const char* msg) {
		
		if (msg != '\0' && msg != nullptr) {
			int length = strlen(msg) + 1;
			error = new char[length];
			strncpy(error, msg, length - 1);
			error[length - 1] = '\0';
		}

		else {
			error = nullptr;
		}
	}
	
	// deallocates memory and clears the message at 
	ErrorState::~ErrorState() {
		delete[] error;
		clear();
	}

	// clears error message and sets it to a safe empty state
	void ErrorState::clear() {
		error = nullptr;
	}

	// checks if the message is cleared or not 
	bool ErrorState::isClear() const {
		if (error == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	// sets message according to specified 
	void ErrorState::message(const char* str) {
			delete[] error;
			int length = strlen(str) + 1;
			error = new char[length];
			strncpy(error, str, length - 1);
			error[length - 1] = '\0';
	}

	// returns error message 
	const char* ErrorState::message() const {
		return error;
	}

	// allows to print out specified object's error message 
	std::ostream& operator<<(std::ostream& ostr, const ErrorState& str) {
		
		if (!str.isClear()) {
			ostr << str.message();
		}
			return ostr;

	}

}
