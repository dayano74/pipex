#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	// F_OK: 存在チェック, R_OK: 読み取り権限のチェック
	if (access("/bin/ls", F_OK | R_OK) == 0)
	{
		printf("i can access!\n");
	}
	else
	{
		perror("accesss");
	}
	return (0);
}
