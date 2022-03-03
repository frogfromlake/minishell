/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:20:25 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/03 23:43:10 by dmontema         ###   ########.fr       */
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

int	builtin_exec(t_table **table, char **environ)
{
	t_table	*curr;
	t_env	**tmp;

	curr = *table;
	tmp = get_env(environ);
	while (curr)
	{
		if (curr->log_op == 0 && check_builtin(curr))
		{
			if (!ft_strcmp((*table)->exe, "pwd"))
				ft_pwd();
			if (!ft_strcmp((*table)->exe, "cd"))
				ft_cd(&curr, tmp);
			if (!ft_strcmp((*table)->exe, "echo"))
				ft_echo(&curr);
			if (!ft_strcmp((*table)->exe, "export"))
				ft_export(tmp, curr);
			if (!ft_strcmp((*table)->exe, "env"))
				ft_env(environ);
			if (!ft_strcmp((*table)->exe, "exit"))
				ft_exit(table);
			if (!ft_strcmp((*table)->exe, "unset"))
				ft_unset(tmp, curr);
		}
		else if (curr->log_op == 0 && !check_builtin(curr))
		{
			if (set_cmd_path(&curr))
				printf("\nError: command not found.\n");
			// else
				// executer(&curr);
		}
		curr = curr->next;
	}
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

	(void) environ;
	(void) table;
	print_shell();
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
				print_cmd_table(*table);
				// builtin_exec(table, environ);
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
	// t_table	*names;
	t_table *table;

	(void) argc;
	(void) argv;
	// names = NULL;
	head = NULL;
	table = NULL;
	bitchy_snake_shell(&head, &table, environ);
	return (0);
}
