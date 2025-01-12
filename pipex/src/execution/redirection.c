/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:29:20 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/12 19:53:15 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/pipex.h"

//append open("./input/binfile.txt", O_WRONLY | O_APPEND);

int	redir_in(char *pathname)
{
	int fd;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		error(NULL, OPEN);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		error(NULL, DUP2);
	}
	return (SUCCESS);
}

int	redir_out(char *pathname)
{
	int fd;

	fd = open(pathname, O_WRONLY | O_CREAT);
	if (fd == -1)
	{
		error(NULL, OPEN);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		error(NULL, DUP2);
	}
	return (SUCCESS);
}
