/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayano <dayano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:23:52 by dayano            #+#    #+#             */
/*   Updated: 2025/03/25 18:46:43 by dayano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// \033 and \e[0m are ANSI escape sequence.
void	usage(void)
{
	ft_putstr_fd("\033[31mError: Bad argument\n\e[0m", 2);
	ft_putstr_fd("Ex: ./pipex file1 cmd1 cmd2 ... cmdn file2\n", 1);
	ft_putstr_fd("    ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file\n", 1);
	exit(EXIT_SUCCESS);
}

// void	pipe_here_doc(int argc, char **argv, char **envp);

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			// pipe_here_doc(argc, argv, envp);
			return (0);
		}
		else
		{
			pipe_multiple(argc, argv, envp);
		}
	}
	usage();
	return (0);
}
