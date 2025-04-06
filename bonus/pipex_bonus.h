/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:56:23 by dayano            #+#    #+#             */
/*   Updated: 2025/04/06 22:10:45 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/incs/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PATH_PREFIX_LEN 5

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE
}					t_node_type;

typedef struct s_node
{
	t_node_type		type;
	char			**cmd;
	struct s_node	*left;
	struct s_node	*right;
	int				is_last;
}					t_node;

typedef struct s_info
{
	int				fd_in;
	int				fd_out;
	char			*infile;
	char			*outfile;
	t_node			*root;
}					t_info;

// main_bonus.c
void				usage(void);

// pipex_bonus.c
void				execute_node(t_node *node, t_info *info, char **envp);

// create_node_bonus.c
t_node				**create_cmd_nodes(int cmd_count, char **argv, int offset);

// build_tree.c
t_node				*build_left_associative_tree(t_node **cmd_nodes,
						int cmd_count);

// execute_cmd_bonus.c
int					is_cmd(char *cmd, char **envp, char **full_path);

// here_doc_bonus.c
void				pipe_here_doc(int argc, char **argv, char **envp);

// pipex_utils_bonus.c
// void				get_fd(char *file1, char *file2, int *fd_in, int *fd_out);
void				mark_last_command(t_node *node);
void				cleanup_and_exit(t_info *info);
void				cleanup_and_exit_status(t_info *info, int status);
void				perror_cleanup_and_exit(char *msg, t_info *info);
void				perror_exit_bonus(char *msg);

// free_bonus.c
void				free_strings(char **str, int n);
void				free_str_array(char **str);
void				free_nodes(t_node **nodes, int n);
void				free_tree(t_node *node);

#endif
