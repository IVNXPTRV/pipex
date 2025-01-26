/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:21:07 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/26 11:20:35 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int handle_infile(t_cntx *cntx, char ***argv)
{

	if (is_heredoc(*(*argv)))
	{
		cntx->heredoc = true;
		(*argv)++;
		redir_heredoc(**argv);
		(*argv)++;
	}
	else
	{
		if(!redir_in(**argv))
		{
			(*argv) += 2;
			return (FAIL);
		}
		(*argv)++;
	}
	return (SUCCESS);
}

static void handle_outfile(t_cntx *cntx, char **argv)
{
	if (*(argv + 2) == NULL)
	{
		if (cntx->heredoc == true)
		{
			redir_append(*(argv + 1));
		}
		else
		{
			redir_out(*(argv + 1));
		}
	}
}

static bool is_cmd(char **argv)
{
	return (*(argv + 1));
}

void execute(t_cntx *cntx, char **argv)
{
	pid_t	pid;
	t_pipe	p;

	handle_infile(cntx, &argv);
	while (is_cmd(argv))
	{
		open_pipe(&p);
		dup2(p.write, STDOUT_FILENO);
		close(p.write);
		handle_outfile(cntx, argv);
		pid = fork();
		if (pid > 0)
		{
			run_cmd(cntx, *argv);
		}
		else if (pid == 0)
		{
			cntx->pid = pid;
			dup2(p.read, STDIN_FILENO);
			close_pipe(&p);
		}
		else
			error(FORK, NULL);
		argv++;
	}
}
