/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:36:16 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/22 16:25:41 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "elibft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_cntx
{
	char **envp;
	bool heredoc;
} t_cntx;

typedef struct s_pipe
{
	int read;
	int write;
} t_pipe;

typedef struct s_cmd
{
	char *path;
	char **argv;
} t_cmd;

//const
typedef enum e_error
{
	MALLOC,
	CMD_NOT_FOUND,
	ERRNO,
	FORK,
	OPEN,
	DUP2,
	GNL,
	FILE_NOT_FOUND,

}	t_error;

//execution
void run_cmd(t_cntx *cntx, char *cmd);
char *get_validpath(t_cntx *cntx, char **argv);
char *get_varvalue(t_cntx *cntx, char *varname);

//redirection
int	redir_in(char *pathname);
int	redir_out(char *pathname);
int	redir_append(char *pathname);
int	redir_heredoc(char *delim);

void open_pipe(t_pipe *p);
void close_pipe(t_pipe *p);

//error
void error(t_cntx *cntx, t_error error);

#endif