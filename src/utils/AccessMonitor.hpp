#ifndef _ACCESS_MONITOR_HPP
#define _ACCESS_MONITOR_HPP

#include <pthread.h>
#include <semaphore.h>


class AccessMonitor {

	sem_t write_access;
	int readers_count = 0;

// To temporarily disable a warning that is triggered by the use of PTHREAD_MUTEX_INITIALIZER
//#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
	pthread_mutex_t new_access          = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t reader_registration = PTHREAD_MUTEX_INITIALIZER;
//#pragma GCC diagnostic pop

public:

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
	AccessMonitor() { sem_init(&this->write_access, 0, 1); }

	// Writer
	// Lock
	void lockWriter() {
		pthread_mutex_lock(&this->new_access);
		sem_wait(&this->write_access);
		pthread_mutex_unlock(&this->new_access);
	}
	// Unlock
	void unlockWriter() {
		sem_post(&this->write_access);
	}

	// Reader
	// Lock
	void lockReader() {
		pthread_mutex_lock(&this->new_access);
		pthread_mutex_lock(&this->reader_registration);
		if (this->readers_count == 0) { sem_wait(&this->write_access); }
		(this->readers_count)++;
		pthread_mutex_unlock(&this->new_access);
		pthread_mutex_unlock(&this->reader_registration);
	}
	// Unlock
	void unlockReader() {
		pthread_mutex_lock(&this->reader_registration);
		(this->readers_count)--;
		if (this->readers_count == 0) { sem_post(&this->write_access); }
		pthread_mutex_unlock(&this->reader_registration);
	}

};

#endif