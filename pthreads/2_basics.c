#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>


static void* routine(void *arg)
{
	int tid = (int)arg;
	pid_t my_pid = getpid();
	printf("[%d] routine, thread #%d, addr:%x\n", 
			my_pid, tid, &my_pid);
	sleep((int)arg);

	printf("[%d] routine, thread #%d, exiting\n", 
			my_pid, tid);
	pthread_exit(NULL);
	//return NULL;
}

int main(int argc, const char **argv)
{
	pid_t my_pid = getpid();
	printf("[%d] pthread_basics\n", my_pid);
	int result;

	pthread_attr_t attr;
	if (result = pthread_attr_init(&attr))
	{
		printf("attr init error %d\n", result);
		return;
	}

	pthread_t threads[3];
	for (int i = 0; i < 3; i++)
	{
		if (result = pthread_create(
					&threads[i], // thread data
					/*&attr*/NULL, // attrs
					routine, // routine to execute
					(void*)i // args for routine
					))
		{
			printf("thread creation error %d\n", result);
			return;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		int tid = 2 - i;
		printf("joining %d\n", tid);
		pthread_join(threads[tid], NULL);
		printf("joined %d\n", tid);
	}

	pthread_exit(NULL);
	return 0;
}
