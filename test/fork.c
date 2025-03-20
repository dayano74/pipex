#include <stdio.h>
#include <unistd.h>

// man 3 fork
// #include <unistd.h>
//
// pid_t fork(void);

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (1);
	}
	if (pid == 0)
	{
		printf("I am the child process!\n");
	}
	else
	{
		printf("I am the parent process! My child has PID %d\n", pid);
	}
	return (0);
}
