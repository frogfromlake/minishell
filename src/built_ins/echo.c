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

#include "../../include/minishell.h"

int	check_empty_arg(char *input)
{
	int	i;

	i = 0;
	while (check_whitespace(input[i]))
		i++;
	if (input[i] == '\0')
		return (1);
	else
		return (0);
}

static bool	check_valid_opt(char *opt)
{
	int	i;

	i = 0;
	if (ft_strncmp(opt, "-n", 2))
		return (false);
	i += 2;
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static int	skip_valid_opt(char **args, bool *opt)
{
	int	i;

	i = 0;
	if (!check_valid_opt(args[i]))
		return (i);
	*opt = true;
	i++;
	while (args[i])
	{
		if (!check_valid_opt(args[i]) && ft_strcmp(args[i], ""))
			break ;
		i++;
	}
	return (i);
}

void	ft_echo(t_table *table)
{
	bool	opt;
	int		i;

	opt = false;
	if (get_arr_size(table->cmd_arr) > 0)
	{
		i = skip_valid_opt(table->cmd_arr, &opt);
		while (table->cmd_arr[i])
		{
			if (!check_empty_arg(table->cmd_arr[i]))
				printf("%s", table->cmd_arr[i]);
			if (ft_strcmp(table->cmd_arr[i], "")
				&& table->cmd_arr[i + 1]
				&& ft_strcmp(table->cmd_arr[i + 1], ""))
				printf(" ");
			i++;
		}
	}
	if (!opt)
		printf("\n");
}
