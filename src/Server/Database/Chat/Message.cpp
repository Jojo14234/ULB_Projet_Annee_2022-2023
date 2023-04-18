#include "Message.hpp"
#include "../User/User.hpp"


Message::operator std::string() {
	std::string output;
	output += writer->getUsername();
	output += ": ";
	output += this->msg;
	return output;
}
