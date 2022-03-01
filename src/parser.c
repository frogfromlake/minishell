/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:24:41 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/01 14:18:44 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_node **node, t_table **table)
{
	t_table	*help;
	t_table	*new;

	help = *table;
	new = NULL;
	create_cmd_table(node, table);
	return (0);
}

void	create_cmd_table(t_node **node, t_table **table)
{
	t_node	*help;
	t_table	*new;

	int		i;

	i = 1;
	help = *node;
	while (help)
	{
		if (help->type == PIPE)
		{
			help = help->next;
			continue;
		}
		new = append_table(table, new_table());
		while (help && help->type != PIPE)
		{
			if (help->type == LESS)
			{
				if (new->redir_in)
					new->redir_in = str_join(new->redir_in, "< ", help->tokens->name);
				else
					new->redir_in = str_join("< ", help->tokens->name, " ");
			}
			if (help->type == GREAT)
			{
				if (new->redir_out)
					new->redir_out = str_join(new->redir_out, "> ", help->tokens->name);
				else
					new->redir_out = str_join("> ", help->tokens->name, " ");
			}
			if (help->type == LESSLESS)
			{
				if (new->redir_in)
					new->redir_in = str_join(new->redir_in, "<< ", help->tokens->name);
				else
					new->redir_in = str_join("<< ", help->tokens->name, " ");
			}
			if (help->type == GREATGREAT)
			{
				if (new->redir_out)
					new->redir_out = str_join(new->redir_out, ">> ", help->tokens->name);
				else
					new->redir_in = str_join(">> ", help->tokens->name, " ");
			}
			else if (help->type == COMMAND)
			{
				new->exe = ft_strdup(help->tokens->name);
				if (!ft_strcmp(new->exe, "echo"))
				{
					if (help->tokens->next)
						echo_parse(help->tokens->next, &new);
				}
				else
				{
					if (help->tokens->next)
						new->args = ft_strjoin(ft_strdup(help->tokens->next->name), "/");
				}
			}
			help = help->next;
		}
	}
}

static bool is_echo_opt_valid(char *opt)
{
	int i;

	i = 1;
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int echo_parse(t_token *help, t_table **new)
{
	bool	echo_opt_valid;

	echo_opt_valid = is_echo_opt_valid(help->name);
	if (echo_opt_valid)
	{
		(*new)->args = ft_strdup("-n");
		help = help->next;
		while (help)
		{
			if (!ft_strcmp(help->name, "-n"))
			{
				help = help->next;
				continue ;
			}
			else
				break ;
		}
		while (help)
		{
			(*new)->args = str_join((*new)->args, " " ,help->name);
			help = help->next;
		}
	}
	else
	{
		(*new)->args = ft_strdup(help->name);
		help = help->next;
		while (help)
		{
			(*new)->args = str_join((*new)->args, " " ,help->name);
			help = help->next;
		}
	}
	return (1);
}