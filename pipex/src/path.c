/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:05:10 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/26 11:24:07 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char *get_varvalue(t_cntx *cntx, char *varname)
{
	char	**envp;
	char	*value;
	size_t	len;

	envp = cntx->envp;
	len = ft_strlen(varname);
	while (*envp)
	{
		value = ft_strnstr(*envp, varname, len);
		if (value)
		{
			return (value + len + 1);
		}
		envp++;
	}
	return (NULL);
}

static char *retrieve_pathname(char *path, char *basename)
{
	char	**dirname;
	char	*pathname;
	size_t	i;

	if (!path)
		return (NULL);
	dirname = ft_split(path, ':');
	if (!dirname)
		error(MALLOC, NULL);
	i = 0;
	while (dirname[i])
	{
		pathname = ft_strjoin(dirname[i], "/");
		pathname = ft_strjoin(pathname, basename);
		if (is_executable(pathname))
			return (pathname);
		free(pathname);
		i++;
	}
	return (NULL);
}

char *get_validpath(t_cntx *cntx, char **argv)
{
	char	*pathname;

	if (is_pathname(argv[0]))
	{
		pathname = argv[0];
		if (is_executable(pathname))
			return (pathname);
	}
	else
	{
		pathname = retrieve_pathname(get_varvalue(cntx, "PATH"), argv[0]);
		if (pathname)
			return (pathname);
	}
	return (NULL);
}
