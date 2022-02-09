/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:20:25 by dmontema          #+#    #+#             */
/*   Updated: 2022/02/09 11:18:46 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	print_ms(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%sminishell@fquist-dmontema%s:", CYAN, RESET);
	printf("%s%s%s$ ", PURPLE, path, RESET);
}

// SIGNAL HANDLING: ctrl + c, ctrl + '\'
// void sig_handl(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		printf("Interrupted.\n");
// 		// print_ms();
// 		return ;
// 	}
// 	else if (sig == SIGQUIT)
// 	{
// 		printf("%d: Quit.\n", sig);
// 		exit(EXIT_SUCCESS);
// 	}
// }

int	main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	char	*usr_input;

	print_ms();
	while (1)
	{
		usr_input = readline(NULL);
		if (!ft_strcmp(usr_input, "pwd"))
		{
			char *path;
			path = getcwd(NULL, 0);
			printf("%s\n", path);
		}
		else
			printf("%sUNKNOWN command%s\n", RED, RESET);
		free(usr_input);
		print_ms();
	}
	// SIGNAL HANDLING: ctrl + c, ctrl + '\'
	// signal(SIGINT, &sig_handl);
	// signal(SIGQUIT, &sig_handl);
	// while (1)
	// {
	// 	pause();
	// }
	return (0);
}