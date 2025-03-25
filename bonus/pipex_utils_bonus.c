/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:33:35 by dayano            #+#    #+#             */
/*   Updated: 2025/03/25 21:51:20 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	get_fd(char *file1, char *file2, int *fd_in, int *fd_out)
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

void	free_strings(char **str, int n)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (i < n)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_str_array(char **str)
{
	int i;

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
