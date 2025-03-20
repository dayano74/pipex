/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:16:07 by dayano            #+#    #+#             */
/*   Updated: 2025/03/18 22:24:11 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	perror_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	free_str_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*get_path_line(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", PATH_PREFIX_LEN) == 0)
			return (envp[i] + PATH_PREFIX_LEN);
		i++;
	}
	return (NULL);
}

char	*join_path(char *dir, char *cmd)
{
	char	*full_path;
	int		len_dir;
	int		len_cmd;

	if (dir[ft_strlen(dir) - 1] == '/')
	{
		full_path = ft_strjoin(dir, cmd);
		if (!full_path)
			return (NULL);
		return (full_path);
	}
	len_dir = ft_strlen(dir);
	len_cmd = ft_strlen(cmd);
	full_path = malloc(len_dir + len_cmd + 2);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, len_dir + 1);
	full_path[len_dir] = '/';
	full_path[len_dir + 1] = '\0';
	ft_strlcpy(full_path + len_dir + 1, cmd, len_cmd + 1);
	return (full_path);
}
