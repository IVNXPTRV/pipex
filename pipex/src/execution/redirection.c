/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:29:20 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/22 16:29:37 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/pipex.h"

//use pipe always cyrcle input inside for each stage
int	redir_heredoc(char *delim)
{
	char *line;
	t_pipe p;
	char *pathname;
	int status;

	open_pipe(&p);
	// fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777); //create and write collected from stdin
	// unlink("here_doc");
	// if (fd == -1) //check all of fd
	// {
	// 	error(NULL, OPEN);
	// }
	while (1)
	{
		ft_printf("> ");
		status = get_next_line(STDIN_FILENO, &line);
		//add that all /n changed to /0 and then manually add /n after EOF echeck
		if (status == ERROR)
		{
			error(NULL, GNL); //close all fd here
		}
		line[ft_strlen(line) - 1] = '\0';
		if (is_eqlstr(line, delim))
		{
			free(line);
			break;
		}
		line[ft_strlen(line)] = '\n';
		ft_putstr_fd(line, p.write); //it should return status of write if error there?
		free(line);
	}
	close(p.write);
	if (dup2(p.read, STDIN_FILENO) == ERROR)
	{
		error(NULL, DUP2);
	}
	close(p.read);
	return (SUCCESS);
}


int	redir_in(char *pathname)
{
	int fd;

	fd = open(pathname, O_RDONLY);
	if (fd == ERROR)
	{
		error(NULL, FILE_NOT_FOUND); //bash: infile: No such file or directory / print this msg
		return (FAIL);
	}
	if (dup2(fd, STDIN_FILENO) == ERROR)
	{
		error(NULL, DUP2);
	}
	close(fd);
	return (SUCCESS);
}

int	redir_out(char *pathname)
{
	int fd;

	fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == ERROR)
	{
		error(NULL, OPEN);
	}
	if (dup2(fd, STDOUT_FILENO) == ERROR)
	{
		error(NULL, DUP2);
	}
	close(fd);
	return (SUCCESS);
}

int	redir_append(char *pathname)
{
	int fd;

	fd = open(pathname, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd == ERROR)
	{
		error(NULL, OPEN);
	}
	if (dup2(fd, STDOUT_FILENO) == ERROR)
	{
		error(NULL, DUP2);
	}
	close(fd);
	return (SUCCESS);
}
