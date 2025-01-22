/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:58:56 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/22 18:44:58 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char *get_error_msg(t_error error)
{
	if (error == INPUT)
		return ("pipex: wrong number of arguments");
	else if (error == EXECVE)
		return ("pipex: command not found");
	return ("");
}
int error(t_error error, void *cntx)
{
	if (error == INPUT)
	{
		ft_putendl_fd(get_error_msg(error), STDERR_FILENO);
		return (FAIL);
	}
	else if (error == EXECVE)
	{
		ft_putendl_fd(get_error_msg(error), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else if (error == FILE_NOT_FOUND)
	{
		perror("pipex");
		return (FAIL);
	}
	else
	{
		perror("pipex");
		exit(EXIT_FAILURE);
		return (FAIL);
	}
}
