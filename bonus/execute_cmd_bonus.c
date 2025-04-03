/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:38:57 by dayano            #+#    #+#             */
/*   Updated: 2025/04/01 13:21:24 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		perror(cmd);
		return (-1);
	}
	return (1);
}
