#include <iostream>

#include <csignal>
#include <unistd.h>


class SigHandler {

	static inline bool sigint_receipt = false;

public:
	static void handler(int sig) { std::cout << sig << std::endl; exit(1); }
};


int main() {

	//SigHandler::handler(SIGINT);

	signal(SIGINT, SigHandler::handler);

	while (true);

	return 0;
}
