#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>


static void* routineA(void *arg)
{
	pthread_mutex_t *mutex = (pthread_mutex_t*)arg;

	pthread_mutex_lock(mutex);
	printf("routineA - start stuff\n");
	sleep(1);
	printf("routineA - end stuff\n");
	pthread_mutex_unlock(mutex);

	pthread_exit(NULL);
}

static void* routineB(void *arg)
{
	pthread_mutex_t *mutex = (pthread_mutex_t*)arg;

	pthread_mutex_lock(mutex);
	printf("routineB - start stuff\n");
	sleep(1);
	printf("routineB - end stuff\n");
	pthread_mutex_unlock(mutex);

	pthread_exit(NULL);
}

int main(int argc, const char **argv)
{
	pthread_t threads[2];

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // static init
	// pthread_mutex_init(&mutex, NULL); // alternative

	pthread_create(&threads[0], NULL, routineA, (void*)&mutex);
	pthread_create(&threads[1], NULL, routineB, (void*)&mutex);

	pthread_exit(NULL);

	//pthread_mutex_destroy(&mutex);
	return 0;
}




