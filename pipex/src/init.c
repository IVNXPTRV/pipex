/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:49:53 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/26 19:51:40 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static	int	init_cntx(t_cntx **cntx)
{
	*cntx = ft_calloc(1, sizeof(t_cntx));
	if (!*cntx)
		return (error(MALLOC, NULL));
	return (SUCCESS);
}

static	int	init_envp(t_cntx *cntx, char **envp)
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

int	init(t_cntx **cntx, char **envp)
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
	(*cntx)->code = 0;
	return (SUCCESS);
}
