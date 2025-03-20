/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:43:56 by dayano            #+#    #+#             */
/*   Updated: 2025/03/20 14:46:15 by dayano           ###   ########.fr       */
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
		perror("file1");
		exit(EXIT_FAILURE);
	}
	*fd_out = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_out < 0)
	{
		perror("file2");
		exit(EXIT_FAILURE);
	}
}

void	execute_pipex(char **argv, char **envp, int fd_in, int fd_out)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
		child_process(argv, envp, pipe_fd, fd_in);
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		parent_process(argv, envp, pipe_fd, fd_out);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	fd_in;
	int	fd_out;

	if (argc != 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	open_files(argv[1], argv[4], &fd_in, &fd_out);
	execute_pipex(argv, envp, fd_in, fd_out);
	return (0);
}
