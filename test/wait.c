#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;
	int		status;
	pid_t	child_pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (1);
	}
	if (pid == 0)
	{
		// 子プロセス：何らかの処理を実行して終了
		printf("Child process is running.\n");
		return (42); // 終了コード 42 を返す
	}
	else
	{
		// 親プロセス：子プロセスの終了を待つ
		child_pid = wait(&status);
		if (child_pid == -1)
		{
			perror("wait failed");
			return (1);
		}
		printf("Parent process\n");
		printf("Child process (PID=%d) terminated. ", child_pid);
		if (WIFEXITED(status))
		{
			printf("Exit status: %d\n", WEXITSTATUS(status));
		}
	}
	return (0);
}
