#ifndef _DATABASE_HPP
#define _DATABASE_HPP

#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "User.hpp"
#include "../../utils/AccessMonitor.hpp"


class Database {
	
	std::vector<User> data;
	const char* path;
    size_t fileSize(FILE *file);
	mutable AccessMonitor am;

public:

	Database(const char* path): path{path} { this->load(); }
	~Database() { this->save(); }

	void load();
	void save();
    void print_in_file();

    void addUser(std::string username, std::string password);

	void addUser(User user) { this->data.push_back(user); }
	void removeUser(User &user) {
		auto it = std::find(this->data.begin(), this->data.end(), user);
		this->data.erase(it);
	}

	bool contains(const int id) const;
	bool contains(const char username[32]) const;
	bool contains(const User &user) const { return this->contains(user.getId()); }

	User* getUser(const int id);
	User* getUser(const char username[32]);

	int getSize() const { return this->data.size(); }

};

#endif
