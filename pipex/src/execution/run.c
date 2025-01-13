/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:04:47 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/13 17:10:36 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	redir_heredoc(char *delim);
int	redir_append(char *pathname);
int apply_redir();

int run_cmd(t_cntx *cntx, char **argv)
{
	char *pathname;

	pathname = get_validpath(cntx, argv);
	apply_redir();
	if (execve(pathname, argv, cntx->envp) == FAIL)
		error(cntx, CMD_NOT_FOUND); //here prnit not found and fully exit() to not allow to go throuw otehr code
	return (SUCCESS);
}
