/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:04:47 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/22 17:46:28 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int run_cmd(t_cntx *cntx, char *cmd)
{
	char	*pathname;
	char	**argv;

	argv = ft_split(cmd, ' ');
	if (argv == NULL)
	{
		return (error(MALLOC, NULL));
	}
	pathname = get_validpath(cntx, argv);
	if (execve(pathname, argv, cntx->envp) == FAIL)
	{
		ft_parrclean(0, free, argv, NULL);
		return (error(EXECVE, NULL));
	}
	return (SUCCESS);
}
