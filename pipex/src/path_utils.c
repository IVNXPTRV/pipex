/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:05:10 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/26 11:26:04 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

bool is_executable(char *pathname)
{
	return (!access(pathname, F_OK | X_OK));
}

bool is_pathname(char *cmd)
{
	return (ft_strchr(cmd, '/'));
}

void remove_dirname(char **argv)
{
	void *ptr;

	ptr = ft_strrchr(*argv, '/');
	if (ptr)
		*argv = ptr + 1;
}
