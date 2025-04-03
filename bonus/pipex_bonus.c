/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:23 by dayano            #+#    #+#             */
/*   Updated: 2025/04/01 22:11:39 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_cmd(t_node *node, t_info *info, char **envp)
{
	char	*cmd_path;
	char	**cmd;

	cmd = node->cmd;
	if (!*cmd || ft_strlen(*cmd) == 0)
		cleanup_and_exit_status(info, 127);
	if (dup2(info->fd_in, STDIN_FILENO) < 0)
		perror_cleanup_and_exit("dup2", info);
	if (dup2(info->fd_out, STDOUT_FILENO) < 0)
		perror_cleanup_and_exit("dup2", info);
	close(info->fd_in);
	close(info->fd_out);
	if (is_cmd(cmd[0], envp, &cmd_path) < 0)
		cleanup_and_exit_status(info, 127);
	if (execve(cmd_path, cmd, envp) < 0)
	{
		free(cmd_path);
		perror_cleanup_and_exit("execve", info);
	}
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

static void	execute_rifht_node(t_node *node, t_info *info, int *pipe_fd,
		char **envp)
{
	t_info	right_info;

	right_info = *info;
	right_info.fd_in = pipe_fd[0];
	close(pipe_fd[1]);
	execute_node(node->right, &right_info, envp);
}

static void	handle_pipe_node(t_node *node, t_info *info, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

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
		execute_rifht_node(node, info, pipe_fd, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	free_tree(info->root);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	exit(EXIT_FAILURE);
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
