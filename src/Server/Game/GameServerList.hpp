#ifndef _GAME_SERVER_LIST_HPP
#define _GAME_SERVER_LIST_HPP

#include "../../utils/List.hpp"
#include "GameServer.hpp"


class GameServerList : public List<GameServer> {

public:
	using List<GameServer>::List;

	std::shared_ptr<GameServer> &createNew() { this->emplace_back(); return this->back(); }

};

#endif