/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:46:13 by dayano            #+#    #+#             */
/*   Updated: 2025/04/10 21:21:49 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_strings(char **str, int n)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (i < n)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_str_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_nodes(t_node **nodes, int n)
{
	int	i;

	if (!nodes)
		return ;
	i = 0;
	while (i < n)
	{
		free_str_array(nodes[i]->cmd);
		free(nodes[i]);
		i++;
	}
	free(nodes);
}

void	free_tree(t_node *node)
{
	if (!node)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	if (node->cmd)
		free_str_array(node->cmd);
	free(node);
}

void	free_perror_cleanup_exit(char *str, char *msg, t_info *info)
{
	free(str);
	perror_cleanup_and_exit(msg, info);
}
