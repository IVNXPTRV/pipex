/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:04:47 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/26 19:11:29 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int handle_null_execv(char **argv, t_cntx *cntx)
{
	ft_parrclean(0, free, argv, NULL);
	ft_parrclean(0, free, cntx->envp, NULL);
	free(cntx);
	return (error(EXECVE, NULL));
}

int run_cmd(t_cntx *cntx, char *cmd)
{
	char	*pathname;
	char	**argv;
	int 	stdin_status;

	argv = NULL;
	if (!cmd || !*cmd)
		handle_null_execv(argv, cntx);
	argv = ft_split(cmd, ' ');
	pathname = get_validpath(cntx, argv);
	if (pathname)
		remove_dirname(argv);
	else
		handle_null_execv(argv, cntx);
	if (cntx->code == 1 || execve(pathname, argv, cntx->envp) == ERROR)
	{
		free(pathname);
		ft_parrclean(0, free, argv, NULL);
		ft_parrclean(0, free, cntx->envp, NULL);
		if (cntx->code == 1)
		{
			free(cntx);
			exit(EXIT_FAILURE);
		}
		free(cntx);
		return (error(EXECVE, NULL));
	}
	return (SUCCESS);
}
