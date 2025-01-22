/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:06:39 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/22 17:47:36 by ipetrov          ###   ########.fr       */
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
	return (SUCCESS);
}

static int wait_all_childs()
{
	while (wait(NULL) != -1)
		;
	return (SUCCESS);
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

	if (!is_valid_input(argc, argv))
	{
		return (EXIT_FAILURE);
	}
	if (init(&cntx, envp) == FAIL)
	{
		return (EXIT_FAILURE);
	}
	execute(cntx, ++argv);
	wait_all_childs();
	return (EXIT_SUCCESS);
}
