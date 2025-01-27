/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:36:16 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/27 20:04:50 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "elibft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>

# define NAME "pipex"

typedef struct s_cntx
{
	char	**envp;
	bool	heredoc;
	pid_t	pid;
	int		code;
}	t_cntx;

typedef struct s_pipe
{
	int		read;
	int		write;
}	t_pipe;

typedef struct s_cmd
{
	char	*path;
	char	**argv;
}	t_cmd;

//const
typedef enum e_error
{
	GENERIC,
	MALLOC,
	CMD_NOT_FOUND,
	FORK,
	OPEN,
	PIPE,
	FILE_NOT_FOUND,
	INPUT,
	HEREDOC_INPUT,
	EXECVE
}	t_error;

//path
char	*get_validpath(t_cntx *cntx, char **argv);

//redirection
int		redir_in(char *pathname);
int		redir_out(char *pathname);
int		redir_append(char *pathname);
int		redir_heredoc(char *delim);

//pipe
int		open_pipe(t_pipe *p);
int		close_pipe(t_pipe *p);
bool	is_pathname(char *cmd);
void	remove_dirname(char **argv);

//utils
bool	is_heredoc(char *argv);
bool	is_executable(char *pathname);

//execution
void	execute(t_cntx *cntx, char **argv);
void	run_cmd(t_cntx *cntx, char *cmd, t_pipe	p);

//error
int		error(t_error error, void *cntx);

//init
int		init(t_cntx **cntx, char **envp);

#endif