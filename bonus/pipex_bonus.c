/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:23 by dayano            #+#    #+#             */
/*   Updated: 2025/03/25 22:01:46 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_cmd(char **cmd, int input_fd, int output_fd, char **envp)
{
	char	*cmd_path;

	// 標準入力・出力をリダイレクト
	if (dup2(input_fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (dup2(output_fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	// 不要なファイルディスクリプタをクローズ
	close(input_fd);
	close(output_fd);
	// コマンドを実行（execve などを呼び出す）
	if (is_cmd(cmd[0], envp, &cmd_path) < 0)
		return ;
	if (execve(cmd_path, cmd, envp) < 0)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	// execvp(cmd[0], cmd);
	// // エラーがあった場合は
	// perror("execvp");
	// exit(EXIT_FAILURE);
}

void	execute_node(t_node *node, int input_fd, int output_fd, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (node == NULL)
		return ;
	if (node->type == NODE_CMD)
	{
		// コマンドノードなら直接実行
		execute_cmd(node->cmd, input_fd, output_fd, envp);
	}
	else if (node->type == NODE_PIPE)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			// 子プロセスで左の子ノードを実行
			// 左側は input_fd -> 左コマンド -> pipe_fd[1]
			close(pipe_fd[0]); // 読み込み側は使わないのでクローズ
			execute_node(node->left, input_fd, pipe_fd[1], envp);
			exit(EXIT_FAILURE); // execve が失敗した場合の対策
		}
		// 親プロセスは右の子ノードを実行する前に子プロセスの終了を待つ（必要に応じて）
		waitpid(pid, NULL, 0);
		// ここで左側の出力は pipe_fd[0] に集約される
		close(pipe_fd[1]); // 書き込み側はもう不要
		// 右側の子ノードを実行
		execute_node(node->right, pipe_fd[0], output_fd, envp);
	}
}

t_node	*create_cmd_node(char **cmd)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node->type = NODE_CMD;
	node->cmd = cmd;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node	**create_cmd_nodes(int argc, char **argv)
{
	t_node	**nodes;
	int		cmd_count;
	char	**cmd_strings;
	int		i;
	char	**args;

	cmd_count = argc - 3;
	nodes = (t_node **)malloc(sizeof(t_node *) * cmd_count);
	if (!nodes)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd_strings = (char **)malloc(sizeof(char *) * (cmd_count + 1));
	if (!cmd_strings)
	{
		perror("malloc");
		free(nodes);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < cmd_count)
	{
		cmd_strings[i] = ft_strdup(argv[i + 2]);
		if (!cmd_strings[i])
		{
			perror("malloc");
			free(nodes);
			free_strings(cmd_strings, i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	cmd_strings[cmd_count] = NULL;
	i = 0;
	while (i < cmd_count)
	{
		args = ft_split(cmd_strings[i], ' ');
		if (!args)
		{
			perror("malloc");
			free(nodes);
			free_strings(cmd_strings, cmd_count);
			free_strings(args, i);
			exit(EXIT_FAILURE);
		}
		nodes[i] = create_cmd_node(args);
		i++;
	}
	free_strings(cmd_strings, i);
	return (nodes);
}

t_node	*create_pipe_node(t_node *left, t_node *right)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node->type = NODE_PIPE;
	node->cmd = NULL;
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*build_left_assosiative_tree(t_node **cmd_nodes, int cmd_count)
{
	t_node	*tree;
	int		i;

	tree = cmd_nodes[0];
	i = 1;
	while (i < cmd_count)
	{
		tree = create_pipe_node(tree, cmd_nodes[i]);
		i++;
	}
	return (tree);
}

void	pipe_multiple(int argc, char **argv, char **envp)
{
	int		fd_in;
	int		fd_out;
	t_node	**cmd_nodes;
	int		cmd_count;
	t_node	*tree;

	get_fd(argv[1], argv[argc - 1], &fd_in, &fd_out);
	cmd_nodes = create_cmd_nodes(argc, argv);
	cmd_count = argc - 3;
	tree = build_left_assosiative_tree(cmd_nodes, cmd_count);
	execute_node(tree, fd_in, fd_out, envp);
}
