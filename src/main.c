/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:20:25 by dmontema          #+#    #+#             */
/*   Updated: 2022/02/22 22:56:59 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static char	*get_prompt(void)
{
	char	*str;

	str = readline("\033[1;32m°º¤ø,¸,ø¤º°`°º¤ø(ಠ_ಠ)┌∩┐:\e[0m");
	return (str);
}

static void	bitchy_snake_shell(t_cmd **head)
{
	char	*read;

	(void)head;
	print_shell();
	while (true)
	{
		read = get_prompt();
		if (read && !ft_strcmp(read, ""))
		{
			// do stuff
		}
		if (EOF || !ft_strcmp(read, "exit"))
		{
			write(1, "logout\n", 8);
			exit(EXIT_SUCCESS);
		}
	}
}

int	main(int argc, char *argv[], char **environ)
{
	t_cmd	*head;

	(void)argc;
	(void)argv;
	(void)environ;
	head = NULL;
	bitchy_snake_shell(&head);
	return (0);
}
