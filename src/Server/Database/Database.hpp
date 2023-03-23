#ifndef _SERVER_DATABASE_HPP
#define _SERVER_DATABASE_HPP

#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "../../utils/AccessMonitor.hpp"
#include "Chat/Conversation.hpp"


class User;

class Database {
	
	std::vector<std::shared_ptr<User>> data;
	std::vector<Conversation> chat;	// not saved in path
	std::string path;
    size_t fileSize(FILE *file);
	mutable AccessMonitor user_am;
	mutable AccessMonitor chat_am;

	Conversation* createConv(User* sender, User* receiver);

	void emplace(const User* user, std::array<const User*, 5> &bests);

public:

	Database(std::string path): path{path} { this->load(); }
	~Database() { this->save(); }
	
	// Load from the db file
	void load();
	// Save to the db file
	void save();
	// Print the data in a file
    void print_in_file();

	// Add a User
	void addUser(User user);
	// Create a user, add and return it
    User* addUser(std::string username, std::string password);
	
	// If the db contains
	bool contains(const int id) const;
	bool contains(const char username[32]) const;
	bool contains(const User &user) const;
	
	// GETTERS
	User* getUser(const int id);
	User* getUser(const char username[32]);
	int getSize() const { return this->data.size(); }
	std::string getUsername(const int id);

    // GetRanking
	int getRankingPos(User* user);
    std::array<const User*, 5> getRanking();
    void resetRanking();
    void sortByRank(int size);

	// Chat
	Conversation* getConv(User* sender, User* receiver);
	void sendMsg(User* sender, User* receiver, const std::string &msg);

};

#endif
