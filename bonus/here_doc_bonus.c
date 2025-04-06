/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:07:17 by dayano            #+#    #+#             */
/*   Updated: 2025/03/31 20:03:34 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	compare_line_with_limiter(int *pipefd, char *limiter)
{
	char	*line;
	size_t	read_size;

	line = NULL;
	write(STDOUT_FILENO, "pipe heredoc> ", 14);
	line = get_next_line(STDIN_FILENO);
	if (!line)
	{
		perror("gnl");
		exit(EXIT_FAILURE);
	}
	read_size = ft_strlen(line);
	if (line[read_size - 1] == '\n')
		line[read_size - 1] = '\0';
	if (ft_strcmp(line, limiter) == 0)
	{
		free(line);
		return (0);
	}
	write(pipefd[1], line, ft_strlen(line));
	write(pipefd[1], "\n", 1);
	free(line);
	return (1);
}

void	pipe_here_doc(int argc, char **argv, char **envp)
{
	int		cmd_count;
	int		pipefd[2];
	t_node	**cmd_nodes;
	t_node	*tree;
	t_info	info;

	if (pipe(pipefd) < 0)
		perror_exit_bonus("pipe");
	while (1)
	{
		if (compare_line_with_limiter(pipefd, argv[2]) == 0)
			break ;
	}
	close(pipefd[1]);
	info.fd_in = pipefd[0];
	info.fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (info.fd_out < 0)
		perror_exit_bonus("open");
	cmd_count = argc - 4;
	cmd_nodes = create_cmd_nodes(cmd_count, &argv[3], 0);
	tree = build_left_associative_tree(cmd_nodes, cmd_count);
	free(cmd_nodes);
	info.root = tree;
	execute_node(tree, &info, envp);
	free_tree(tree);
}
