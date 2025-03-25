#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/incs/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PATH_PREFIX_LEN 5

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE
}				t_node_type;

typedef struct s_node
{
	t_node_type	type;
	char **cmd;           // NODE_CMD の場合のみ有効。例: {"ls", "-l", NULL}
	struct s_node *left;  // NODE_PIPE の場合、左の子ノード
	struct s_node *right; // NODE_PIPE の場合、右の子ノード
}				t_node;

// pipex_bonus.c
void			pipe_multiple(int argc, char **argv, char **envp);

// pipex_utils_bonus.c
void			get_fd(char *file1, char *file2, int *fd_in, int *fd_out);
void			free_strings(char **str, int n);
void			free_str_array(char **str);

// execute_cmd_bonus.c
int				is_cmd(char *cmd, char **envp, char **full_path);

#endif
