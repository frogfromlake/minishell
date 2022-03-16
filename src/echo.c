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

// FIXME: case [echo -n "$USERR" -n] should print last arg (-n)
// FIXME: case [echo hello"world"] should print without whitespace (helloworld)
// FIXME: case [echo $]
// FIXME: case [echo $ $?]
// FIXME: case [echo $ $?]
// FIXME: case [echo $"USER"]
// FIXME: case [echo $U]
// FIXME: case [$USER.$]
// FIXME: case [$USER .$]
// FIXME: case [echo $USER.$$]
// FIXME: case [echo HELLO"$USER"$USER]
// FIXME: case [echo HELLO"$USER"]
// FIXME: case [echo $USER$PATH]

void	ft_echo(t_table *table)
{
	if (table->args)
		printf("%s", table->args);
	if (!table->opt)
		printf("\n");

	// int		i;
	// char	*res;

	// i = 3;
	// res = malloc(sizeof(char));
	// if (table->exe && !table->args)
	// 	printf("\n");
	// else if (table->exe && !ft_strncmp(table->args, "-n ", 3))
	// {
	// 	while (table->args[i])
	// 	{
	// 		ft_putchar_fd(table->args[i], 1);
	// 		i++;
	// 	}
	// }
	// else if ((table->exe && !ft_strcmp(table->args, "-n")
	// 		&& ft_strlen(table->args) < 3) || (table->exe
	// 		&& !ft_strcmp(table->args, "\"-n\"")
	// 		&& ft_strlen(table->args) < 5))
	// 	return ;
	// else
	// {
	// 	res = ft_strtrim(table->args, "\"");
	// 	ft_putstr_fd(table->args, 1);
	// 	write(1, "\n", 1);
	// 	free(res);
	// }
	
}
