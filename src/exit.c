/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:35:21 by fquist            #+#    #+#             */
/*   Updated: 2022/03/01 14:21:26 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
