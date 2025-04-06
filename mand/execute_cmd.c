/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:31:23 by dayano            #+#    #+#             */
/*   Updated: 2025/04/01 18:19:12 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*find_cmd_in_paths(char **path_set, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_set[i])
	{
		full_path = join_path(path_set[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	*path_line;
	char	**path_set;
	char	*full_path;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	path_line = get_path_line(envp);
	if (!path_line)
		return (NULL);
	path_set = ft_split(path_line, ':');
	if (!path_set)
		return (NULL);
	full_path = find_cmd_in_paths(path_set, cmd);
	free_str_array(path_set);
	return (full_path);
}

int	is_cmd(char *cmd, char **envp, char **full_path)
{
	*full_path = get_cmd_path(cmd, envp);
	if (!*full_path)
	{
		return (-1);
	}
	return (1);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**args;

	if (!cmd || ft_strlen(cmd) == 0)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", STDERR_FILENO);
		exit(127);
	}
	args = ft_split(cmd, ' ');
	if (!args)
	{
		free_str_array(args);
		perror_exit("ft_split");
	}
	if (is_cmd(args[0], envp, &cmd_path) < 0)
	{
		free_str_array(args);
		perror_exit_status(cmd, 127);
	}
	if (execve(cmd_path, args, envp) < 0)
	{
		free_str_array(args);
		free(cmd_path);
		perror_exit("execve");
	}
}
