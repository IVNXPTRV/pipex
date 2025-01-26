/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:06:39 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/26 15:45:28 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int init_cntx(t_cntx **cntx)
{
	*cntx = ft_calloc(1, sizeof(t_cntx));
	if (!*cntx)
		return (error(MALLOC, NULL));
	return (SUCCESS);
}

static int init_envp(t_cntx *cntx, char **envp)
{
	size_t	len;
	int		i;

	len = ft_parrlen(envp);
	cntx->envp = ft_calloc(len + 1, sizeof(char *));
	if (!cntx->envp)
		return (error(MALLOC, NULL));
	i = 0;
	if (envp[i] == NULL)
	{
		cntx->envp[i] = NULL;
		return (SUCCESS);
	}
	while (i < len)
	{
		cntx->envp[i] = ft_strdup(envp[i]);
		if (!cntx->envp[i])
		{
			ft_parrclean(0, free, cntx->envp, NULL);
			return (error(MALLOC, NULL));
		}
		i++;
	}
	cntx->envp[i] = NULL;
	return (SUCCESS);
}

static int init(t_cntx **cntx, char **envp)
{
	if (init_cntx(cntx) == FAIL)
		return (FAIL);
	if (init_envp(*cntx, envp) == FAIL)
	{
		free(*cntx);
		return (FAIL);
	}
	(*cntx)->heredoc = false;
	(*cntx)->pid = -1;
	return (SUCCESS);
}

static int get_exitcode(pid_t pid)
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

static bool is_valid_input(int argc, char **argv)
{
	if (argc < 5)
	{
		return (error(INPUT, NULL));
	}
	else if (is_heredoc(*(++argv)) && argc == 5)
	{
		return (error(INPUT, NULL));;
	}
	else
	{
		return (SUCCESS);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cntx *cntx;
	int	exitcode;

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
