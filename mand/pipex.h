/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:21:06 by dayano            #+#    #+#             */
/*   Updated: 2025/04/10 19:29:20 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define PATH_PREFIX_LEN 5

# include "../libft/incs/libft.h"

// main.c
void	validate_args(int argc);
void	execute_pipex(char **argv, char **envp);
void	child_process(char **argv, char **envp, int *pipe_fd);
void	second_child_process(char **argv, char **envp, int *pipe_fd);

// execute_cmd.c
void	execute_cmd(char *cmd, char **envp);

// pipex_utils.c
void	perror_exit(char *msg);
void	perror_exit_status(char *msg, int status);
void	free_str_array(char **str);
char	*get_path_line(char **envp);
char	*join_path(char *dir, char *cmd);

#endif
