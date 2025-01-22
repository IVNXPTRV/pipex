/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:06:39 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/22 14:28:40 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int run_pipeline(t_cntx *cntx, char * **cmd);

int init_cntx(t_cntx **cntx)
{
	*cntx = ft_calloc(1, sizeof(t_cntx));
	if (!*cntx)
		return (FAIL);
	return (SUCCESS);
}

int init_envp(t_cntx *cntx, char **envp)
{
	size_t	len;
	int		i;

	len = ft_parrlen(envp);
	cntx->envp = ft_calloc(len + 1, sizeof(char *));
	if (!cntx->envp)
		return (FAIL);
	i = 0;
	if (envp[i] == NULL)
	{
		cntx->envp[i] = NULL;
		return (SUCCESS);
	}
	while (i < len)
	{
		cntx->envp[i] = ft_strdup(envp[i]);
		if (!cntx->envp[i])
		{
			ft_parrclean(0, free, cntx->envp, NULL);
			return (FAIL);
		}
		i++;
	}
	cntx->envp[i] = NULL;
	return (SUCCESS);
}

int init(t_cntx **cntx, char **envp)
{
	if (init_cntx(cntx) == FAIL)
		return (FAIL);
	if (init_envp(*cntx, envp) == FAIL)
		return (FAIL);
	(*cntx)->heredoc = false;
	return (SUCCESS);
}

bool is_heredoc(char *argv);
int execute(t_cntx *cntx, char **argv);

int wait_all_childs()
{
	while (wait(NULL) != -1)
		;
	return (SUCCESS);
}

// ./pipex here_doc EOF ls .. | cat | /bin/cat >> outfile.txt
int	main(int argc, char **argv, char **envp)
{
	t_cntx *cntx;

	if (argc < 5)
	{
		// error(1);
		//print msg: should be at least 4 arguments
		printf("should be 4 arg\n");
		return (EXIT_FAILURE);
	}
	if (is_heredoc(*(++argv)) && argc == 5)
	{
		//error
		//print msg: if heredoc should me at least 5 args
		printf("heredoc error\n");
		return (EXIT_FAILURE);
	}

	if (init(&cntx, envp) == FAIL)
	{
		return (EXIT_FAILURE);
	}

	execute(cntx, argv);
	wait_all_childs();
	// run_pipeline(cntx, NULL);
	// run_cmd(cntx, cmd);
	return (EXIT_SUCCESS);
}
