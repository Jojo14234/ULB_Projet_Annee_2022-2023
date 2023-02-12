#ifndef _ACCESS_MONITOR_HPP
#define _ACCESS_MONITOR_HPP

#include <pthread.h>
#include <semaphore.h>


class AccessMonitor {

	sem_t write_access;
	pthread_mutex_t new_access          = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t reader_registration = PTHREAD_MUTEX_INITIALIZER;
	int readers_count = 0;

public:

	// Writer
	void lockWriter() {
		pthread_mutex_lock(&this->new_access);
		sem_wait(&this->write_access);
		pthread_mutex_unlock(&this->new_access);
	}

	void unlockWriter() {
		sem_post(&this->write_access);
	}

	// Reader
	void lockReader() {
		pthread_mutex_lock(&this->new_access);
		pthread_mutex_lock(&this->reader_registration);
		if (this->readers_count == 0) { sem_wait(&this->write_access); }
		(this->readers_count)++;
		pthread_mutex_unlock(&this->new_access);
		pthread_mutex_unlock(&this->reader_registration);
	}

	void unlockReader() {
		pthread_mutex_lock(&this->reader_registration);
		(this->readers_count)--;
		if (this->readers_count == 0) { sem_post(&this->write_access); }
		pthread_mutex_unlock(&this->reader_registration);
	}

};

#endif
