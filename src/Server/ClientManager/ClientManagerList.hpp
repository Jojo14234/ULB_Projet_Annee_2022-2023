#ifndef _CLIENT_MANAGER_LIST_HPP
#define _CLIENT_MANAGER_LIST_HPP

#include <pthread.h>

#include "../../utils/List.hpp"
#include "ClientManager.hpp"


class ClientManagerList : public List<ClientManager> {

public:

	using List<ClientManager>::List;

	void clean() {
		this->am.lockWriter();
		for ( auto &cm : *this ) {
			if ( cm->isDisconnected() ) {
				pthread_join(*(cm->getTidPtr()), NULL);
				this->remove(*cm);
			}	
		}
		this->am.unlockWriter();
	}
};

#endif
