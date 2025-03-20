#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	int		newfd;
	char	buff[100];

	// ファイル "example.txt" を読み取り専用で開く
	fd = open("example.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open failed");
		return (1);
	}
	// dup を使って fd を複製する
	newfd = dup(fd);
	if (newfd == -1)
	{
		perror("dup failed");
		return (1);
	}
	// ここで、fd と newfd は同じファイルを指しており、
	// 両方ともファイルの先頭など、同じ位置を指しています。
	printf("fd = %d, newfd = %d\n", fd, newfd);
	read(newfd, buff, sizeof(buff));
	printf("newfd = %d, %s\n", newfd, buff);
	// 両方のディスクリプタを閉じる
	close(fd);
	close(newfd);
	return (0);
}
