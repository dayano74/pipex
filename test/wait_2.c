#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		// 子プロセス
		printf("子プロセスです。\n");
		sleep(2); // 子プロセスが2秒待機後終了
		printf("子プロセス終了。\n");
		exit(0);
	}
	else
	{
		// 親プロセス
		printf("親プロセスです。子プロセス終了を待ちます。\n");
		wait(NULL); // 子プロセスの終了を待つ
		printf("子プロセスが終了しました。\n");
	}
	return (0);
}
