/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:06:39 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/26 19:51:26 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	get_exitcode(pid_t pid)
{
	int		status;
	pid_t	child;
	int		exitcode;

	child = 0;
	exitcode = 1;
	while (child != -1)
	{
		child = wait(&status);
		if (child == pid)
		{
			if (WIFEXITED(status))
			{
				exitcode = WEXITSTATUS(status);
			}
		}
	}
	return (exitcode);
}

static bool	is_valid_input(int argc, char **argv)
{
	if (argc < 5)
	{
		return (error(INPUT, NULL));
	}
	else if (is_heredoc(*(++argv)) && argc == 5)
	{
		return (error(INPUT, NULL));
	}
	else
	{
		return (SUCCESS);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cntx	*cntx;
	int		exitcode;

	if (!is_valid_input(argc, argv))
	{
		return (EXIT_FAILURE);
	}
	if (init(&cntx, envp) == FAIL)
	{
		return (EXIT_FAILURE);
	}
	execute(cntx, ++argv);
	exitcode = get_exitcode(cntx->pid);
	ft_parrclean(0, free, cntx->envp, NULL);
	free(cntx);
	return (exitcode);
}
