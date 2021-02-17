#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

static void f1_fork();
static void f2_pthread_basics();
static void f3_pthread_mutexes();
static void f4_pthread_condvars();

int main(int argc, const char **argv)
{
	printf("\n\nWelcome!\n");
	printf("Program executed with %d args:\n", argc);
	for (int i = 0; i < argc; i++)
		printf("%s\n", argv[i]);

	//f1_fork();
//	f2_pthread_basics();
	//f3_pthread_mutexes();
	f4_pthread_condvars();


	printf("\nDone.\n");
	return 0;
}

static void f1_fork()
{
	int child = 0;
	for (int i = 0; i < 2 && !child; i++)
	{
		pid_t frk = fork();
		pid_t my_pid = getpid();

		printf("[%d] Forked!\n", my_pid);
		child = frk == 0;

		if (child)
			printf("[%d] Child here\n", my_pid);
		else
			printf("[%d] Parent here, my child has PID %d\n", my_pid, frk);
	}

}

static void* f2_routine(void *arg)
{
	int tid = (int)arg;
	pid_t my_pid = getpid();
	printf("[%d] f2_routine, thread #%d, addr:%x\n", 
			my_pid, tid, &my_pid);
	sleep((int)arg);

	printf("[%d] f2_routine, thread #%d, exiting\n", 
			my_pid, tid);
	pthread_exit(NULL);
	//return NULL;
}

static void f2_pthread_basics()
{
	pid_t my_pid = getpid();
	printf("[%d] f2_pthread_basics\n", my_pid);
	int result;

	pthread_attr_t attr;
	if (result = pthread_attr_init(&attr))
	{
		printf("f2 - attr init error %d\n", result);
		return;
	}

	pthread_t threads[3];
	for (int i = 0; i < 3; i++)
	{
		if (result = pthread_create(
					&threads[i], // thread data
					/*&attr*/NULL, // attrs
					f2_routine, // routine to execute
					(void*)i // args for routine
					))
		{
			printf("f2 - thread creation error %d\n", result);
			return;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		int tid = 2 - i;
		printf("f2 - joining %d\n", tid);
		pthread_join(threads[tid], NULL);
		printf("f2 - joined %d\n", tid);
	}

	pthread_exit(NULL);
}


static void* f3_routineA(void *arg)
{
	pthread_mutex_t *mutex = (pthread_mutex_t*)arg;

	pthread_mutex_lock(mutex);
	printf("f3_routineA - start stuff\n");
	sleep(1);
	printf("f3_routineA - end stuff\n");
	pthread_mutex_unlock(mutex);

	pthread_exit(NULL);
}

static void* f3_routineB(void *arg)
{
	pthread_mutex_t *mutex = (pthread_mutex_t*)arg;

	pthread_mutex_lock(mutex);
	printf("f3_routineB - start stuff\n");
	sleep(1);
	printf("f3_routineB - end stuff\n");
	pthread_mutex_unlock(mutex);

	pthread_exit(NULL);
}

static void f3_pthread_mutexes()
{
	pthread_t threads[2];

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // static init
	// pthread_mutex_init(&mutex, NULL); // alternative

	pthread_create(&threads[0], NULL, f3_routineA, (void*)&mutex);
	pthread_create(&threads[1], NULL, f3_routineB, (void*)&mutex);

	pthread_exit(NULL);

	//pthread_mutex_destroy(&mutex);
}

typedef struct {
	pthread_mutex_t *mutex;
	pthread_cond_t *condvar;
} f4_data ;

static void* f4_routineA(void *arg)
{
	f4_data *data = (f4_data*)arg;
	printf("f4_routineA\n");
	printf("f4_routineA - waiting\n");
	pthread_cond_wait(data->condvar, data->mutex);
	printf("f4_routineA - condition fulfilled\n");

	pthread_exit(NULL);
}

static void* f4_routineB(void *arg)
{
	f4_data *data = (f4_data*)arg;
	printf("f4_routineB\n");
	sleep(2);
	printf("f4_routineB - signaling\n");
	pthread_cond_signal(data->condvar);
	pthread_exit(NULL);
}


static void f4_pthread_condvars()
{
	pthread_t threads[2];

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;// static init, dynamic is also possible as with mutexes
	f4_data data = {
		.mutex = &mutex,
		.condvar = &condvar
	};

	pthread_create(&threads[0], NULL, f4_routineA, (void*)&data);
	pthread_create(&threads[1], NULL, f4_routineB, (void*)&data);

	pthread_exit(NULL);
}
