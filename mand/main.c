/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:43:56 by dayano            #+#    #+#             */
/*   Updated: 2025/04/01 20:25:36 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	open_files(char *file1, char *file2, int *fd_in, int *fd_out)
{
	*fd_in = open(file1, O_RDONLY);
	if (*fd_in < 0)
	{
		perror(file1);
		*fd_in = open("/dev/null", O_RDONLY);
		if (*fd_in < 0)
			perror_exit("open /dev/null");
	}
	*fd_out = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_out < 0)
	{
		perror(file2);
		*fd_out = STDOUT_FILENO;
	}
}

void	execute_pipex(char **argv, char **envp, int fd_in, int fd_out)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(pipe_fd) < 0)
		perror_exit("pipe");
	pid1 = fork();
	if (pid1 < 0)
		perror_exit("fork");
	if (pid1 == 0)
		child_process(argv, envp, pipe_fd, fd_in);
	pid2 = fork();
	if (pid2 < 0)
		perror_exit("fork");
	if (pid2 == 0)
		second_child_process(argv, envp, pipe_fd, fd_out);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd_in;
	int	fd_out;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", STDERR_FILENO);
		return (1);
	}
	open_files(argv[1], argv[4], &fd_in, &fd_out);
	execute_pipex(argv, envp, fd_in, fd_out);
}
