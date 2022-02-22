/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:24:41 by dmontema          #+#    #+#             */
/*   Updated: 2022/02/10 17:56:03 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	add_cmds(t_cmd **cmd_list, char **args)
// {
// 	int i;

// 	i = 0;
// 	while (args[i])
// 	{
// 		if (*(args[i]) == '|')
// 		{
			
// 		}
// 	}
// }

static void free_split(char **args)
{
	int i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

void print_args(char **args)
{
	int i;

	i = 0; 
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
}

int	parser(t_cmd **commands, char *usr_input)
{
	(void)	commands;
	char	**args;

	args = ft_split(usr_input, ' ');
	print_args(args);
	
	free_split(args);
	return (1);
}
