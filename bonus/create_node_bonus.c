/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node__bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:51:45 by dayano            #+#    #+#             */
/*   Updated: 2025/03/31 20:51:47 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static t_node	*create_cmd_node(char **cmd)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		perror_exit_bonus("malloc");
	node->type = NODE_CMD;
	node->cmd = cmd;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static char	**get_cmd_strings(int cmd_count, char **argv, int offset)
{
	char	**cmd_strings;
	int		i;

	i = 0;
	cmd_strings = (char **)malloc(sizeof(char *) * (cmd_count + 1));
	if (!cmd_strings)
		perror_exit_bonus("malloc");
	i = 0;
	while (i < cmd_count)
	{
		cmd_strings[i] = ft_strdup(argv[i + offset]);
		if (!cmd_strings[i])
		{
			free_strings(cmd_strings, i);
			perror_exit_bonus("malloc");
		}
		i++;
	}
	cmd_strings[cmd_count] = NULL;
	return (cmd_strings);
}

static t_node	**create_cmd_nodes_from_strings(char **cmd_strings,
		t_node **nodes, int cmd_count)
{
	char	**args;
	int		i;

	i = 0;
	while (i < cmd_count)
	{
		args = ft_split(cmd_strings[i], ' ');
		if (!args)
		{
			if (i > 0)
				free_nodes(nodes, i);
			else
				free(nodes);
			free_strings(cmd_strings, cmd_count);
			perror_exit_bonus("malloc");
		}
		nodes[i] = create_cmd_node(args);
		i++;
	}
	return (nodes);
}

t_node	**create_cmd_nodes(int cmd_count, char **argv, int offset)
{
	t_node	**nodes;
	char	**cmd_strings;

	cmd_strings = get_cmd_strings(cmd_count, argv, offset);
	nodes = (t_node **)malloc(sizeof(t_node *) * cmd_count);
	if (!nodes)
	{
		free_strings(cmd_strings, cmd_count);
		perror_exit_bonus("malloc");
	}
	nodes = create_cmd_nodes_from_strings(cmd_strings, nodes, cmd_count);
	free_strings(cmd_strings, cmd_count);
	return (nodes);
}
