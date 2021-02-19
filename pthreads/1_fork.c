#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, const char **argv)
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

	return 0;
}
