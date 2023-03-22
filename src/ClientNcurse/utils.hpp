#ifndef _CLIENT_UTILS_HPP_
#define _CLIENT_UTILS_HPP_


enum class STATE { CONNECTION, MENU, GAME };


class Subject {
public:
	virtual void update() = 0;
	virtual void getmenfou() {}
};


#endif // _CLIENT_UTILS_HPP_
