/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:23 by dayano            #+#    #+#             */
/*   Updated: 2025/04/12 18:35:29 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_cmd(t_node *node, t_info *info, char **envp)
{
	char	*cmd_path;
	char	**cmd;

	cmd = node->cmd;
	if (!*cmd || ft_strlen(*cmd) == 0)
	{
		ft_putstr_fd("Command '' not found\n", STDERR_FILENO);
		cleanup_and_exit_status(info, 127);
	}
	if (dup2(info->fd_in, STDIN_FILENO) < 0)
		perror_cleanup_and_exit("dup2", info);
	if (dup2(info->fd_out, STDOUT_FILENO) < 0)
		perror_cleanup_and_exit("dup2", info);
	close(info->fd_in);
	close(info->fd_out);
	if (is_cmd(cmd[0], envp, &cmd_path) < 0)
	{
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		cleanup_and_exit_status(info, 127);
	}
	if (execve(cmd_path, cmd, envp) < 0)
		free_perror_cleanup_exit(cmd_path, "execve", info);
}

static void	execute_left_node(t_node *node, t_info *info, int *pipe_fd,
		char **envp)
{
	t_info	left_info;

	left_info = *info;
	left_info.fd_out = pipe_fd[1];
	close(pipe_fd[0]);
	execute_node(node->left, &left_info, envp);
	exit(EXIT_FAILURE);
}

static void	execute_right_node(t_node *node, t_info *info, int *pipe_fd,
		char **envp)
{
	t_info	right_info;

	right_info = *info;
	right_info.fd_in = pipe_fd[0];
	close(pipe_fd[1]);
	if (node->right && node->right->type == NODE_CMD && node->right->is_last)
	{
		right_info.fd_out = open(info->outfile, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (right_info.fd_out < 0)
		{
			perror(info->outfile);
			free_tree(info->root);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		right_info.fd_out = info->fd_out;
	}
	execute_node(node->right, &right_info, envp);
	free_tree(info->root);
	exit(EXIT_FAILURE);
}

static void	handle_pipe_node(t_node *node, t_info *info, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(pipe_fd) == -1)
		perror_cleanup_and_exit("pipe", info);
	pid_left = fork();
	if (pid_left < 0)
		perror_cleanup_and_exit("fork", info);
	if (pid_left == 0)
		execute_left_node(node, info, pipe_fd, envp);
	pid_right = fork();
	if (pid_right < 0)
		perror_cleanup_and_exit("fork", info);
	if (pid_right == 0)
		execute_right_node(node, info, pipe_fd, envp);
	close_pipe_and_info(info, pipe_fd);
	wait_and_exit(info, pid_left, pid_right);
}

void	execute_node(t_node *node, t_info *info, char **envp)
{
	if (node == NULL)
		return ;
	if (node->type == NODE_CMD)
		execute_cmd(node, info, envp);
	else if (node->type == NODE_PIPE)
		handle_pipe_node(node, info, envp);
}
