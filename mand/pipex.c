/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:16:07 by dayano            #+#    #+#             */
/*   Updated: 2025/04/06 20:21:21 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	child_process(char **argv, char **envp, int *pipe_fd)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
	{
		perror(argv[1]);
	}
	if (dup2(fd_in, STDIN_FILENO) < 0)
	{
		exit(EXIT_FAILURE);
	}
	if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
	{
		exit(EXIT_FAILURE);
	}
	close(fd_in);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_cmd(argv[2], envp);
	exit(EXIT_FAILURE);
}

void	second_child_process(char **argv, char **envp, int *pipe_fd)
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		perror(argv[4]);
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
	{
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_out, STDOUT_FILENO) < 0)
	{
		exit(EXIT_FAILURE);
	}
	close(fd_out);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_cmd(argv[3], envp);
	exit(EXIT_FAILURE);
}
