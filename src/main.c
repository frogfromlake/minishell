/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:20:25 by dmontema          #+#    #+#             */
/*   Updated: 2022/02/23 22:27:46 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	check_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

static int	check_empty_input(char *input)
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

static char	*get_prompt(void)
{
	char	*str;

	str = readline("\033[1;32m°º¤ø,¸,ø¤º°`°º¤ø(ಠ_ಠ)┌∩┐: \e[0m");
	return (str);
}

static void	bitchy_snake_shell(t_node **head)
{
	char	*read;

	(void)head;
	print_shell();
	while (true)
	{
		read = get_prompt();
		if (read != NULL && ft_strcmp(read, ""))
		{
			add_history(read);
			if (!check_empty_input(read))
			{
				// do stuff
				lexer(head, read);
				print_nodes(*head);
			}
			free_list(head, false, false);
		}
		if (read == NULL || !ft_strcmp(read, "exit"))
		{
			write(1, "logout\n", 8);
			exit(EXIT_SUCCESS);
		}
		// if (!ft_strcmp(read, "pwd"))
		// {
		// 	printf("%s\n", get_cwd());
		// }
	}
}

int	main(int argc, char *argv[], char **environ)
{
	t_node	*head;

	(void)argc;
	(void)argv;
	(void)environ;
	head = NULL;
	bitchy_snake_shell(&head);
	return (0);
}
