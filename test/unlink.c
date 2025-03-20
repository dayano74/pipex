#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	if (unlink("oldfile.txt") == 0)
	{
		printf("oldfile.txt has been deleted.\n");
	}
	else
	{
		perror("unlink failed");
	}
	return (0);
}
