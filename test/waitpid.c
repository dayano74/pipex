#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (1);
	}
	if (pid == 0)
	{
		// 子プロセス：何かの処理をして終了
		printf("Child process is running.\n");
		sleep(2); // 少し待ってから終了
		return (0);
	}
	else
	{
		// 親プロセス：特定の子プロセス (pid) の終了を待つ
		printf("pid = %d\n", pid);
		pid_t ret = waitpid(pid, &status, 0); // 0 はオプションなし＝ブロックする
		if (ret == -1)
		{
			perror("waitpid failed");
			return (1);
		}
		printf("Child process (PID=%d) terminated.\n", ret);
	}
	return (0);
}
