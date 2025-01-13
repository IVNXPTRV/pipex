/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:36:16 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/13 09:35:51 by ipetrov          ###   ########.fr       */
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
} t_cntx;


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

}	t_error;

//execution
int run_cmd(t_cntx *cntx, char **argv);
char *get_validpath(t_cntx *cntx, char **argv);
char *get_varvalue(t_cntx *cntx, char *varname);

//redirection
int	redir_in(char *pathname);

//error
void error(t_cntx *cntx, t_error error);

#endif