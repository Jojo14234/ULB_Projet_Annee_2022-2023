#include <iostream>
#include <csignal>
#include <unistd.h>

#include "SigHandler.hpp"


// Static Public

void SigHandler::setup() {
	signal(SIGINT, SigHandler::handler);
	signal(SIGPIPE, SIG_IGN);  // Mask SIGPIPE

	struct sigaction action;
	action.sa_handler = SigHandler::handler;
	action.sa_flags = 0;
	if (sigemptyset(&action.sa_mask) < 0) {
		perror("sigemptyset()");
	} else if (sigaction(SIGINT, &action, NULL) < 0) {
		perror("sigaction()");
	}
}

void SigHandler::handler(int sig) {
	switch(sig) {
		case SIGINT:
			std::cout << "\nSIGINT Caught" << std::endl;
			SigHandler::sigint_receipt = true;
			break;
	}
}

void SigHandler::mask() {
	sigemptyset(&mask_ptr);
	sigaddset(&mask_ptr, SIGINT);
	sigprocmask(SIG_BLOCK, &mask_ptr, NULL);
}

void SigHandler::unmask() {
	sigprocmask(SIG_UNBLOCK, &mask_ptr, NULL);
}
