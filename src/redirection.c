/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:29:20 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/26 20:03:49 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

bool	is_heredoc(char *argv)
{
	return (is_eqlstr(argv, "here_doc"));
}

int	redir_heredoc(char *delim)
{
	char	*line;
	t_pipe	p;
	t_file	*fl;

	open_pipe(&p);
	while (1)
	{
		ft_printf("> ");
		get_next_line(STDIN_FILENO, &line, &fl);
		line[ft_strlen(line) - 1] = '\0';
		if (is_eqlstr(line, delim))
		{
			free(line);
			break ;
		}
		line[ft_strlen(line)] = '\n';
		ft_putstr_fd(line, p.write);
		free(line);
	}
	dup2(p.read, STDIN_FILENO);
	close_pipe(&p);
	free(fl);
	return (SUCCESS);
}

int	redir_in(char *pathname)
{
	int		fd;
	t_pipe	p;

	fd = open(pathname, O_RDONLY);
	if (fd == ERROR)
	{
		open_pipe(&p);
		close(p.write);
		fd = p.read;
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (error(FILE_NOT_FOUND, NULL));
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

int	redir_out(char *pathname)
{
	int	fd;

	fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == ERROR)
	{
		return (error(OPEN, NULL));
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

int	redir_append(char *pathname)
{
	int	fd;

	fd = open(pathname, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd == ERROR)
	{
		return (error(OPEN, NULL));
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}
