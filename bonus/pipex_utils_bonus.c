/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:33:35 by dayano            #+#    #+#             */
/*   Updated: 2025/04/06 22:10:29 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// void	get_fd(char *file1, char *file2, int *fd_in, int *fd_out)
// {
// 	*fd_in = open(file1, O_RDONLY);
// 	if (*fd_in < 0)
// 	{
// 		perror(file1);
// 		// *fd_in = open("/dev/null", O_RDONLY);
// 		// if (*fd_in < 0)
// 		// 	perror_exit_bonus("open /dev/null");
// 	}
// 	*fd_out = open(file2, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (*fd_out < 0)
// 	{
// 		perror(file2);
// 		// *fd_out = STDOUT_FILENO;
// 	}
// }

void	mark_last_command(t_node *node)
{
	if (!node)
	{
		return ;
	}
	if (node->type == NODE_PIPE)
		mark_last_command(node->right);
	else if (node->type == NODE_CMD)
		node->is_last = 1;
}

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
