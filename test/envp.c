#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	// 環境変数を順番に表示してみる
	// while (envp[i])
	// {
	// 	printf("envp[%d]: %s\n", i, envp[i]);
	// 	i++;
	// }
	printf("%s\n", envp[20]);
	return (0);
}
