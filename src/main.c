/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:20:25 by dmontema          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/15 00:33:55 by fquist           ###   ########.fr       */
=======
/*   Updated: 2022/03/14 20:05:45 by dmontema         ###   ########.fr       */
>>>>>>> 47d600115760da6d4dbf8d3b62535ad9f76b58aa
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

int	built_in_exec(t_table *table)
{
	if (table->log_op == 0 && table->exe && check_builtin(table))
	{
		if (!ft_strcmp(table->exe, "pwd"))
			ft_pwd();
		if (!ft_strcmp(table->exe, "cd"))
			ft_cd(table);
		if (!ft_strcmp(table->exe, "echo"))
			ft_echo(table, -1);
		if (!ft_strcmp(table->exe, "export"))
			ft_export(table);
		if (!ft_strcmp(table->exe, "env"))
			ft_env();
		if (!ft_strcmp(table->exe, "exit"))
			ft_exit(table);
		if (!ft_strcmp(table->exe, "unset"))
			ft_unset(table);
		return (1);
	}
	return (0);
}

static void	bitchy_snake_shell(t_node **head, t_table **table)
{
	char	*read;

	print_header();
	// system("(afplay welcome.mp3&)");
	// system("(afplay snake.mp3&)");
	while (true)
	{
		read = get_prompt();
		if (read != NULL && ft_strcmp(read, ""))
		{
			add_history(read);
			if (!check_empty_input(read))
			{
				lexer(head, read);
				// print_nodes(*head);
				// print_nodes(*head);
				expander(head);
				parser(head, table);
				// free_node(head);
				// print_cmd_table(*table);
				// built_in_exec(*table);
				// printf("REDIR IS: %d\n", *(int *)(*table)->redir_in->content);
				exec_loop(*table);
				// print_cmd_table(*table);
			}
			free_table(table, false, false);
			free_list(head, false, false);
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
	get_env(environ);
	bitchy_snake_shell(&head, &table);
	return (0);
}
