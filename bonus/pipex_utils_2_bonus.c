/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:01:57 by dayano            #+#    #+#             */
/*   Updated: 2025/04/12 18:31:57 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	mark_last_command(t_node *node)
{
	if (!node)
	{
		return ;
	}
	if (node->type == NODE_PIPE)
	{
		node->is_last = 0;
		mark_last_command(node->right);
	}
	else if (node->type == NODE_CMD)
		node->is_last = 1;
}

void	initialize_is_last(t_node *node)
{
	if (!node)
		return ;
	node->is_last = 0;
	initialize_is_last(node->left);
	initialize_is_last(node->right);
}

void	close_pipe_and_info(t_info *info, int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (info->fd_in >= 0)
	{
		close(info->fd_in);
		info->fd_in = -1;
	}
	if (info->fd_out >= 0)
	{
		close(info->fd_out);
		info->fd_out = -1;
	}
}

void	wait_and_exit(t_info *info, pid_t pid_left, pid_t pid_right)
{
	int	status;

	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	free_tree(info->root);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	exit(EXIT_FAILURE);
}
