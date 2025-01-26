/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:04:47 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/26 17:24:54 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int run_cmd(t_cntx *cntx, char *cmd)
{
	char	*pathname;
	char	**argv;
	int 	stdin_status;

	argv = ft_split(cmd, ' ');
	if (argv == NULL)
	{
		return (error(MALLOC, NULL));
	}
	pathname = get_validpath(cntx, argv);
	if (pathname)
		remove_dirname(argv);
	if (execve(pathname, argv, cntx->envp) == ERROR)
	{
		ft_parrclean(0, free, argv, NULL);
		ft_parrclean(0, free, cntx->envp, NULL);
		free(cntx);
		return (error(EXECVE, NULL));
	}
	return (SUCCESS);
}
