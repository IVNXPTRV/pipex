/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:36:16 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/12 13:27:19 by ipetrov          ###   ########.fr       */
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

#endif