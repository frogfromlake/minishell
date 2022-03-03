/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelix <nelix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:35:21 by fquist            #+#    #+#             */
/*   Updated: 2022/03/03 03:59:46 by nelix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(t_table **table)
{
	t_table	*cmd;

	cmd = *table;
	if (!ft_strcmp(cmd->exe, "exit"))
	{
		// free stuff
		write(1, "logout\n", 8);
		exit(EXIT_SUCCESS);
	}
}
