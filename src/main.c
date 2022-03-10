/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:20:25 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/10 17:50:27 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	check_builtin(t_table *table)
{
	if (!ft_strcmp(table->exe, "pwd")
		|| !ft_strcmp(table->exe, "cd")
		|| !ft_strcmp(table->exe, "echo")
		|| !ft_strcmp(table->exe, "export")
		|| !ft_strcmp(table->exe, "env")
		|| !ft_strcmp(table->exe, "exit")
		|| !ft_strcmp(table->exe, "unset"))
		return (true);
	return (false);
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

char	*get_prompt(void)
{
	char	*str;
	char	*colorized;

	str = "\033[0;32m °º¤ø,¸,ø¤º°`°º¤ø(ಠ_ಠ)┌∩┐$ \e[0m";
	colorized = ft_strjoin(GREEN, ft_strrchr(getcwd(NULL, 0), '/'));
	return (readline(ft_strjoin(colorized, str)));
}

static void	bitchy_snake_shell(t_node **head, t_table **table, char **environ)
{
	char	*read;
	t_env	**tmp;

	tmp = get_env(environ);
	print_header();
	while (true)
	{
		read = get_prompt();
		if (read != NULL && ft_strcmp(read, ""))
		{
			add_history(read);
			if (!check_empty_input(read))
			{
				lexer(head, read);
				print_nodes(*head);
				parser(head, table);
				// free_node(head);
				// print_cmd_table(*table);
				// builtin_exec(table, tmp);
				executer(table, tmp);
				// print_cmd_table(*table);
			}
			free_table(table, false, false);
			free_list(head, false, false);
			// system("leaks minishell");
		}
	}
}

int	main(int argc, char *argv[], char **environ)
{
	t_node	*head;
	t_table	*table;

	(void) argc;
	(void) argv;
	head = NULL;
	table = NULL;
	bitchy_snake_shell(&head, &table, environ);
	return (0);
}
