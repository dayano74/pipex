#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;
	int		status;
	pid_t	wpid;
	int		exit_status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		// 子プロセス: 終了ステータス 42 で終了
		exit(42);
	}
	else
	{
		// 親プロセス: waitpid を用いて子プロセスの終了を待つ
		wpid = waitpid(pid, &status, 0);
		if (wpid == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		// 正常終了かどうかを確認
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			printf("子プロセスは終了ステータス %d で終了しました。\n", exit_status);
			if (exit_status != 42)
			{
				fprintf(stderr, "テスト失敗: 期待値 42, 実際の終了ステータス %d\n", exit_status);
				exit(EXIT_FAILURE);
			}
			exit(exit_status);
			exit(EXIT_SUCCESS);
		}
		else
		{
			fprintf(stderr, "子プロセスが正常に終了しませんでした。\n");
			exit(EXIT_FAILURE);
		}
	}
	printf("テスト成功。\n");
	return (0);
}
