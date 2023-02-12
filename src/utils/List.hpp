#ifndef _LIST_HPP
#define _LIST_HPP

#include <vector>
#include <memory>
#include <pthread.h>
#include <semaphore.h>

#include "AccessMonitor.hpp"


template<typename T>
class List : protected std::vector<std::shared_ptr<T>> {

protected:

	mutable AccessMonitor am;

public:
	using std::vector<std::shared_ptr<T>>::vector;

	void add(const std::shared_ptr<T> &elem) {
		this->am.lockWriter();
		this->push_back(elem);
		this->am.unlockWriter();
	}
	
	void remove(const T &elem) {
		this->am.lockWriter();
		for ( auto &it : *this ) { 
			if ( *it == elem ) {	
				auto tmp = this->back();
				this->pop_back();
				it = tmp;
				break;
			}
		} this->am.unlockWriter();
	}

};

#endif
