#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int	main(void)
{
	int	fd;

	fd = open("noexist.txt", O_RDONLY);
	if (fd == -1)
	{
		// strerrorでエラー内容を取得して自由に表示できる
		printf("Error: %s\n", strerror(errno));
	}
}
