/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:19:47 by fquist            #+#    #+#             */
/*   Updated: 2022/03/10 15:48:39 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(t_table *table, int fd)
{
	int		i;
	char	*res;

	i = 3;
	res = malloc(sizeof(char));
	if (fd < 0)
		fd = 1;
	if (table->exe && !table->args)
		printf("\n");
	else if (table->exe && !ft_strncmp(table->args, "-n ", 3))
	{
		while (table->args[i])
		{
			ft_putchar_fd(table->args[i], fd);
			i++;
		}
	}
	else if ((table->exe && !ft_strcmp(table->args, "-n")
			&& ft_strlen(table->args) < 3) || (table->exe
			&& !ft_strcmp(table->args, "\"-n\"")
			&& ft_strlen(table->args) < 5))
		return ;
	else
	{
		res = ft_strtrim(table->args, "\"");
		ft_putstr_fd(table->args, fd);
		write(fd, "\n", 1);
		free(res);
	}
	return ;
}
