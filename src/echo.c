/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:19:47 by fquist            #+#    #+#             */
/*   Updated: 2022/03/01 15:51:37 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(t_table **table)
{
	int		i;
	char	*res;

	i = 3;
	res = malloc(sizeof(char));
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
	else if (((*table)->exe && !ft_strcmp((*table)->args, "-n")
			&& ft_strlen((*table)->args) < 3) || ((*table)->exe
			&& !ft_strcmp((*table)->args, "\"-n\"")
			&& ft_strlen((*table)->args) < 5))
		return ;
	else
	{
		res = ft_strtrim((*table)->args, "\"");
		printf("%s\n", res);
		free(res);
	}
	return ;
}
