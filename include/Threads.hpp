#ifndef THREADS
#define THREADS
#include <pthread.h>
extern pthread_mutex_t lock;
#define lock_thread() pthread_mutex_lock(&lock);
#define unlock_thread() pthread_mutex_unlock(&lock);
#endif