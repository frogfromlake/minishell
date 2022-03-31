/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:48:10 by fquist            #+#    #+#             */
/*   Updated: 2022/03/31 22:20:10 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_exit_status;

int	check_empty_input(char *input)
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
	t_stringbuilder	*prompt;
	char			*path;
	char			*ret;

	prompt = sb_create();
	path = getcwd(NULL, 0);
	sb_append_str(prompt, CYAN);
	sb_append_str(prompt, ft_strrchr(path, '/'));
	sb_append_str(prompt, "\033[0;32m °º¤ø,¸,ø¤º°`°º¤ø(ಠ_ಠ)┌∩┐ ");
	sb_append_str(prompt, GREEN);
	sb_append_str(prompt, "@");
	sb_append_str(prompt, getenv("USER"));
	sb_append_str(prompt, "$ \e[0m");
	ret = sb_get_str(prompt);
	sb_destroy(prompt);
	free(path);
	return (ret);
}

static void	snake_shell(t_node **head, t_table **table, char *read)
{
	add_history(read);
	if (!check_empty_input(read))
	{
		lexer(head, read);
		expander(head);
		parser(head, table);
		if (g_exit_status == SUCCESS)
		{
			change_termios(false);
			exec_loop(*table);
		}
	}
}

static void	reset_snake_shell(t_node **head, t_table **table, char *read)
{
	int		s_out;
	int		s_in;

	s_out = dup(STDOUT_FILENO);
	s_in = dup(STDIN_FILENO);
	free_node(head);
	free_table(table);
	free(read);
	dup2(s_in, STDIN_FILENO);
	dup2(s_out, STDOUT_FILENO);
}

void	init_snake_shell(t_node **head, t_table **table)
{
	char	*read;
	char	*tmp;

	print_header();
	while (true)
	{
		handle_interactive();
		tmp = get_prompt();
		read = readline(tmp);
		free(tmp);
		if (read != NULL && ft_strcmp(read, ""))
			snake_shell(head, table, read);
		reset_snake_shell(head, table, read);
		if (!read)
		{
			write(2, "exit\n", 5);
			free_env();
			break ;
		}
	}
}
