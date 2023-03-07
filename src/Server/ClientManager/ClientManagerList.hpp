#ifndef _SERVER_CLIENT_MANAGER_LIST_HPP
#define _SERVER_CLIENT_MANAGER_LIST_HPP

#include <iostream>
#include <pthread.h>

#include "../../utils/List.hpp"
#include "ClientManager.hpp"


class ClientManagerList : public List<ClientManager> {
public:
	using List<ClientManager>::List;

	// Join the ended threads
	// Remove the ended ClientManager from the list
	void clean() {
		this->am.lockWriter();
		for ( auto &cm : *this ) {
			if ( cm->isDisconnected() ) {
				pthread_join(*(cm->getTidPtr()), NULL);
				this->remove(*cm, true);
			}
		}
		this->am.unlockWriter();
	}
};

#endif