/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:04:47 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/12 19:52:55 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int run_cmd(t_cntx *cntx, char **argv)
{
	char *pathname;
	pid_t pid;

	pathname = get_validpath(cntx, argv);
	if (!pathname)
	{
		error(cntx, CMD_NOT_FOUND);
		return (FAIL);
	}
	pid = fork();
	if (pid == 0)
	{
		redir_in("./infile");
		redir_out("./outfile");
		if (execve(pathname, argv, cntx->envp) == -1)
			error(cntx, CMD_NOT_FOUND);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	else
	{
		error(cntx, FORK);
	}
	return (SUCCESS);
}
