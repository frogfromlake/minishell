/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:25:35 by fquist            #+#    #+#             */
/*   Updated: 2022/03/12 01:32:23 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	child_wait_pid(pid_t *pid, int n)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	status = status >> 8;
	status = status & 0x000000ff;
	return (status);
}
