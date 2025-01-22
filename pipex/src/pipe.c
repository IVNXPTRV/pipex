/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:40:32 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/22 17:50:48 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int open_pipe(t_pipe *p)
{
	int fd[2];

	if (pipe(fd) == ERROR)
	{
		return (error(PIPE, NULL));
	}
	p->read = fd[0];
	p->write = fd[1];
	return (SUCCESS);
}

int close_pipe(t_pipe *p)
{
	close(p->read);
	close(p->write);
	return (SUCCESS);
}
