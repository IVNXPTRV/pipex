/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:37:48 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/13 13:37:54 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_pipex.h"

int	main(void)
{
    char *args[] = {"/bin/ls", "-l", NULL};  // Arguments for the command
    execve("/bin/ls", args, NULL);           // Execute the 'ls' command with '-l' argument
	return (EXIT_SUCCESS);
}
