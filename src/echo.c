/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:19:47 by fquist            #+#    #+#             */
/*   Updated: 2022/03/01 03:04:56 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(t_table **table)
{
	int	i;

	i = 3;
	if ((*table)->exe && !(*table)->args)
		printf("\n");
	else if ((*table)->exe && !ft_strncmp((*table)->args, "-n ", 3))
	{
		while ((*table)->args[i])
		{
			printf("%c", (*table)->args[i]);
			i++;
		}
	}
	else if ((*table)->exe && !ft_strcmp((*table)->args, "-n")
		&& ft_strlen((*table)->args) < 3)
		return ;
	else
		printf("%s\n", (*table)->args);
	return ;
}