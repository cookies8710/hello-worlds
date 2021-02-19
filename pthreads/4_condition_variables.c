#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
	pthread_mutex_t *mutex;
	pthread_cond_t *condvar;
} data ;

static void* routineA(void *arg)
{
	data *d = (data*)arg;
	printf("routineA\n");
	printf("routineA - waiting\n");
	pthread_cond_wait(d->condvar, d->mutex);
	printf("routineA - condition fulfilled\n");

	pthread_exit(NULL);
}

static void* routineB(void *arg)
{
	data *d = (data*)arg;
	printf("routineB\n");
	sleep(2);
	printf("routineB - signaling\n");
	pthread_cond_signal(d->condvar);
	pthread_exit(NULL);
}

int main(int argc, const char **argv)
{
	//
	pthread_t threads[2];

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;// static init, dynamic is also possible as with mutexes
	data d = {
		.mutex = &mutex,
		.condvar = &condvar
	};

	pthread_create(&threads[0], NULL, routineA, (void*)&d);
	pthread_create(&threads[1], NULL, routineB, (void*)&d);

	pthread_exit(NULL);

	return 0;
}

