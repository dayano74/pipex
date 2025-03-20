// #include <unistd.h>

// int pipe(int pipefd[2]);

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	int		pipefd[2];
	char	buffer[100];
	pid_t	pid;
	char	message[] = "Hello from parent!";
	size_t	bytes_read;

	// 1. パイプの作成
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	// 2. プロセスの分岐
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{ // 子プロセス
		// 3. 子は書き込み側が不要なので閉じる
		close(pipefd[1]);
		// 4. パイプからデータを読み取る
		bytes_read = read(pipefd[0], buffer, sizeof(buffer));
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			printf("Child received: %s\n", buffer);
		}
		// 使用後は読み取り側も閉じる
		close(pipefd[0]);
	}
	else
	{ // 親プロセス
		// 3. 親は読み取り側が不要なので閉じる
		close(pipefd[0]);
		// 4. パイプにメッセージを書き込む
		write(pipefd[1], message, strlen(message));
		// 使用後は書き込み側も閉じる
		close(pipefd[1]);
	}
	return (0);
}
