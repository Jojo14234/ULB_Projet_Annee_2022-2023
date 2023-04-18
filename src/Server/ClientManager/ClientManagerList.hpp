#ifndef _SERVER_CLIENT_MANAGER_LIST_HPP
#define _SERVER_CLIENT_MANAGER_LIST_HPP

#include <iostream>
#include <pthread.h>

#include "../../Utils/List.hpp"
#include "ClientManager.hpp"


class ClientManagerList : public List<ClientManager> {
public:
	using List<ClientManager>::List;
    using List<ClientManager>::begin;
    using List<ClientManager>::end;

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