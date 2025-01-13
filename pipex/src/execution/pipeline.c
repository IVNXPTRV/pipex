/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:54:48 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/13 18:33:12 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int run_cmd(t_cntx *cntx, char **argv);

//and mb create wrapper open_pipe()
void open_pipe(t_pipe *p)
{
	int *fd[2];

	pipe(*fd); //mb here handle errors???
	p->read = fd[0];
	p->write = fd[1];
}

//change to close_pipe()
void close_pipe(t_pipe *p)
{
	close(p->read);
	close(p->write);
}

int setup_producer(t_cntx *cntx, int write, char **cmd) //to setup first only to be producer
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(write, STDOUT_FILENO);
		run_cmd(cntx, *cmd);
	}
	return (pid);
}

//for everyone between setup them to be producer and consumer
int setup_mediators(t_cntx *cntx, int *read, char ****cmd)
{
	pid_t pid;
	int fd[2];
	t_pipe p;

	while (**(cmd + 1))
	{
		open_pipe(&p);
		pid = fork();
		if (pid == 0)
		{
			dup2(*read, STDIN_FILENO);
			dup2(p.write, STDOUT_FILENO);
			run_cmd(cntx, **cmd); //close fd for pipe if cmd failed??
		}
		*read = p.read;
		(*cmd)++;
	}
	return (pid);
}

int setup_consumer(t_cntx *cntx, int read, char **cmd) //to setup last to be consumer
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(read, STDIN_FILENO);
		run_cmd(cntx, *cmd);
	}
	return (pid);
}

//make waitpid handler separate
int get_pipeline_exitcode(pid_t pid)
{
	int		status;
	pid_t	child;
	int		exitcode;

	child = 0;
	exitcode = -1;
	while (child != -1)
	{
		child = wait(&status);
		if (child == pid)
		{
			if (WIFEXITED(status))
			{
				exitcode = WEXITSTATUS(status);
			}
		}
	}
	return (exitcode);
}

//at least 2 commands as input
int run_pipeline(t_cntx *cntx, char ***cmd)
{
	t_pipe p;
	pid_t pid;

	open_pipe(&p);
	pid = setup_producer(cntx, p.write, cmd);//to setup first only to be producer // make them return not pid but cmd
	pid = setup_mediators(cntx, &p.read, &cmd);
	pid = setup_consumer(cntx, p.read, cmd);
	close_pipe(&p);
	get_pipeline_exitcode(pid);

	//cat | cat | la | cat




	// pipe(fd); //check error
	// pid = fork(); //create pipeline space
	// if (pid == 0)
	// {
	// 	while (*cmd)
	// 	{
	// 		pid = fork(); //we fork pipeline sapce to subst by execve of cmd
	// 		if (pid == 0)
	// 		{
	// 			run_cmd(*cmd);
	// 		}
	// 		else if (pid > 0)
	// 		{
	// 			cmd++;
	// 			//we need somehow coolect exit_code
	// 		}
	// 		else
	// 		{
	// 			error(cntx, FORK);
	// 		}
	// 	}
	// 	wait(NULL); //collects exit_code of each cmd??
	// }
	// else if (pid > 0)
	// 	wait(NULL); //get result of pipeline space / exit_code
}
