/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:49:36 by dayano            #+#    #+#             */
/*   Updated: 2025/03/31 20:51:53 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static t_node	*create_pipe_node(t_node *left, t_node *right)
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

t_node	*build_left_associative_tree(t_node **cmd_nodes, int cmd_count)
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
