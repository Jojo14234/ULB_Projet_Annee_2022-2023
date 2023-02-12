#ifndef _SIG_HANDLER_HPP
#define _SIG_HANDLER_HPP

#include <csignal>
#include <unistd.h>
#include <memory>


class SigHandler {

	static inline bool sigint_receipt = false;
	static inline sigset_t* mask_ptr =  new sigset_t;

public:
	
	// To avoid errors
	SigHandler()=delete;	

	// Setup the principal interrupt handler
	static void setup();	
	
	// The handler for signals
	static void handler(int sig);

	// Mask signals
	static void mask();
	// Unmask signals
	static void unmask();

	// If a SIGINT has been received
	static bool askedLeaving() { return SigHandler::sigint_receipt; }

};

#endif