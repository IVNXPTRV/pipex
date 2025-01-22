/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:21:07 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/22 15:32:53 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

bool is_heredoc(char *argv)
{
	return(is_eqlstr(argv, "here_doc"));
}

//and mb create wrapper open_pipe()
void open_pipe(t_pipe *p)
{
	int fd[2];

	pipe(fd); //mb here handle errors??? //check error
	p->read = fd[0];
	p->write = fd[1];
}

//change to close_pipe()
void close_pipe(t_pipe *p)
{
	close(p->read);
	close(p->write);
}

void handle_infile(t_cntx *cntx, char **argv)
{
	if (is_heredoc(*argv)) //1st arg open and dup
	{
		cntx->heredoc = true;
		redir_heredoc(*(++argv));
		//set cntx mode for last append
	}
	else
	{
		redir_in(*argv++);
		//open ordinary file
	}
}

void handle_outfile(t_cntx *cntx, char **argv)
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
bool is_cmd(char **argv)
{
	return (*(argv + 1));
}

// ./pipex here_doc EOF "ls .." | cat | /bin/cat >> outfile.txt
int execute(t_cntx *cntx, char **argv)
{
	pid_t pid;
	t_pipe p;

	handle_infile(cntx, argv);
	argv++;
	while (is_cmd(argv))
	{
		open_pipe(&p);
		dup2(p.write, STDOUT_FILENO);
		handle_outfile(cntx, argv);

		pid = fork();
		if (pid == 0)
		{
			close(p.write);
			run_cmd(cntx, *argv);
			exit(EXIT_FAILURE);
		}
		else if (pid == -1)
		{
			//error
		}
		else
		{
			dup2(p.read, STDIN_FILENO);
			close(STDOUT_FILENO);
			close_pipe(&p);
		}
		argv++;
	}

	return (SUCCESS);
}

