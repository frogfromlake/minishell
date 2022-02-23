/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:24:41 by dmontema          #+#    #+#             */
/*   Updated: 2022/02/23 18:33:10 by fquist           ###   ########.fr       */
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

int	parser(t_token **commands, char *usr_input)
{
	(void)	commands;
	char	**args;

	args = ft_split(usr_input, ' ');
	print_args(args);
	
	free_split(args);
	return (1);
}
