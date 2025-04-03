/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:23:52 by dayano            #+#    #+#             */
/*   Updated: 2025/04/01 22:12:46 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// \033 and \e[0m are ANSI escape sequence.
void	usage(void)
{
	ft_putstr_fd("\033[31mError: Bad argument\n\e[0m", STDERR_FILENO);
	ft_putstr_fd("Ex: ./pipex file1 cmd1 cmd2 ... cmdn file2\n", STDERR_FILENO);
	ft_putstr_fd("    ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file\n",
		STDERR_FILENO);
	exit(EXIT_SUCCESS);
}

static void	pipe_multiple(int argc, char **argv, char **envp)
{
	t_info	info;
	t_node	**cmd_nodes;
	int		cmd_count;
	t_node	*tree;

	get_fd(argv[1], argv[argc - 1], &info.fd_in, &info.fd_out);
	cmd_count = argc - 3;
	cmd_nodes = create_cmd_nodes(cmd_count, argv, 2);
	tree = build_left_associative_tree(cmd_nodes, cmd_count);
	free(cmd_nodes);
	info.root = tree;
	execute_node(tree, &info, envp);
	free_tree(tree);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			pipe_here_doc(argc, argv, envp);
		}
		else
		{
			pipe_multiple(argc, argv, envp);
		}
	}
	usage();
	return (0);
}
