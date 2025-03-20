#include <stdio.h>
#include <unistd.h>

// #include <unistd.h>

// int	execve(const char *pathname, char *const argv[], char *const envp[]);

int	main(void)
{
	char	*args[] = {"ls", "-l", NULL};

	// 環境変数はここでは NULL を指定（必要に応じて環境変数の配列を渡す）
	if (execve("/bin/ls", args, NULL) == -1)
	{
		perror("execve failed");
		return (1);
	}
	// execve が成功すれば、ここには到達しません
	printf("not print if execve succeed\n");
	return (0);
}
