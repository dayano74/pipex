/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:19:22 by dayano            #+#    #+#             */
/*   Updated: 2025/03/13 20:50:07 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

// #include <unistd.h>

// int pipe(int fildes[2]);
// pid_t fork(void);

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		pipefd[2];
	char	buffer[100];
	int		bytes_read;
	int		tmp_fd;

	if (pipe(pipefd[2]) < 0)
	{
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		bytes_read = read(pipefd[0], buffer, sizeof(buffer));
		while (bytes_read != 0)
		{
			if (bytes_read < 0)
			{
				close(pipefd[0]);
				close(pipefd[1]);
				exit(EXIT_FAILURE);
			}
			write(pipefd[1], buffer, strlen(buffer));
			bytes_read = read(pipefd[0], buffer, sizeof(buffer));
		}
		tmp_fd = dup(pipefd[1]);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	else
	{
		wait(NULL);
	}
	return (0);
}
