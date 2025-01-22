/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:58:56 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/22 17:46:03 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char *get_error_msg(t_error error)
{
	if (error == INPUT)
		return ("pipex: wrong number of arguments");
	return ("");
}
int error(t_error error, void *cntx)
{
	if (error == INPUT)
	{
		ft_putendl_fd(get_error_msg(INPUT), STDERR_FILENO);
		return (FAIL);
	}
	else
	{
		perror("pipex: ");
		exit(EXIT_FAILURE);
		return (FAIL);
	}
}
