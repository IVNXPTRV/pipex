/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:04:47 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/22 14:25:32 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

//close fd for pipe if cmd failed??
//this function runs already inside of fork if new process nedded
//it doesnt create new process
void run_cmd(t_cntx *cntx, char *cmd)
{
	char *pathname;
	char **argv;

	// apply_redirs();
	//BUILT-IN: check here if cmd is built-in and run without execve
	argv = ft_split(cmd, ' ');
	if (argv == NULL)
	{
		return ;
	}
	pathname = get_validpath(cntx, argv);
	execve(pathname, argv, cntx->envp);
	ft_parrclean(0, free, argv, NULL);
	// if (execve(pathname, argv, cntx->envp) == FAIL)
	// 	error(cntx, CMD_NOT_FOUND); //here prnit not found and fully exit() to not allow to go throuw otehr code
	return ;
}
