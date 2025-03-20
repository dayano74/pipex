#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	fd;

	// ファイル "output.txt" を書き込み用に開く（存在しなければ作成）
	fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open failed");
		return (1);
	}
	// dup2 を使って、標準出力 (fd 1) を fd に複製する
	// つまり、これ以降の printf() の出力は "output.txt" に書き込まれる
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		return (1);
	}
	// ここで、標準出力が output.txt にリダイレクトされる
	printf("This message goes to output.txt instead of the terminal.\n");
	// 使用後は必ず閉じる（この例では fd と STDOUT_FILENO の両方）
	close(fd);
	printf("done\n");
	return (0);
}
