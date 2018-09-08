
// Final Project Milestone 2 - ErrorState Class
// ErrorState.h
// Date	2018-07-19
// Author	Sean Surjanto

#ifndef ERRORSTATE_H
#define ERRORSTATE_H

namespace AMA {

	class ErrorState {

		char* error;

	public:

		ErrorState();
		ErrorState(const char*);
		ErrorState(const ErrorState&) = delete;
		virtual ~ErrorState();
		void clear();
		bool isClear() const;
		void message(const char*);
		const char* message() const;

	};

	std::ostream& operator<<(std::ostream&, const ErrorState&);

}
#endif // !ERRORSTATE_H