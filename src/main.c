/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:20:25 by dmontema          #+#    #+#             */
/*   Updated: 2022/02/10 20:58:00 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// returns 1 if str is one of the builtin funcs

// int is_builtin(char *str)
// {
// 	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "echo -n"))
// 	if (!ft_strcmp(str, "echo"))
// }

static void	print_ms(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%sminishell@fquist-dmontema%s:", CYAN, RESET);
	printf("%s%s%s$ ", PURPLE, path, RESET);
}

int	main(int argc, char *argv[], char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	char	*usr_input;
	t_cmd	*commands;

	// printf("%s\n", *envp);
	print_ms();
	while (1)
	{
		usr_input = readline(NULL);
		parser(&commands, usr_input);
		free(usr_input);
		print_ms();
	}
	return (0);
}