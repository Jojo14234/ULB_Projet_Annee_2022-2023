#ifndef _CLIENT_UTILS_HPP_
#define _CLIENT_UTILS_HPP_


enum class STATE { CONNECTION, MENU, GAME };


class Subject {
public:
	virtual void update() = 0;
};


#endif // _CLIENT_UTILS_HPP_
