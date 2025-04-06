/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:43:56 by dayano            #+#    #+#             */
/*   Updated: 2025/04/06 20:08:36 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	execute_pipex(char **argv, char **envp)
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
		child_process(argv, envp, pipe_fd);
	pid2 = fork();
	if (pid2 < 0)
		perror_exit("fork");
	if (pid2 == 0)
		second_child_process(argv, envp, pipe_fd);
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
	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", STDERR_FILENO);
		return (1);
	}
	execute_pipex(argv, envp);
}
