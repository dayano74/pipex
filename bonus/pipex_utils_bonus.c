/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:33:35 by dayano            #+#    #+#             */
/*   Updated: 2025/04/12 15:02:09 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	cleanup_and_exit(t_info *info)
{
	if (info->root)
		free_tree(info->root);
	exit(EXIT_FAILURE);
}

void	cleanup_and_exit_status(t_info *info, int status)
{
	if (info->root)
		free_tree(info->root);
	exit(status);
}

void	perror_cleanup_and_exit(char *msg, t_info *info)
{
	perror(msg);
	cleanup_and_exit(info);
}

void	perror_exit_bonus(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
