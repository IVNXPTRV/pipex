/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:29:20 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/13 09:49:22 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/pipex.h"

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

int	redir_append(char *pathname)
{
	int fd;

	fd = open(pathname, O_WRONLY | O_APPEND);
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

int	here_doc(char *delim)
{
	char *line;
	int fd[4];
	char *pathname;

	fd[0] = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777); //create and write collected from stdin
	fd[1] = open("here_doc", O_RDONLY); //read for expantion
	fd[3] = open("here_doc", O_WRONLY); //result of expanstion
	fd[4] = open("here_doc", O_RDONLY); //final read
	unlink("here_doc");
	if (fd[0] == -1) //check all of fd
	{
		error(NULL, OPEN);
	}
	while (1)
	{
		if (!get_next_line(STDIN_FILENO, &line))
		{
			error(NULL, GNL); //close all fd here
		}
		if (is_eqlstr(line, delim))
		{
			free(line);
			break;
		}
		ft_putstr_fd(line, fd[0]); //it should return status of write if error there?
		free(line);
	}
	close(fd[0]);
	if (dup2(fd[1], STDIN_FILENO) == -1)
	{
		error(NULL, DUP2);
	}
	return (SUCCESS);
}
