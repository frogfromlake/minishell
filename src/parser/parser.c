/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:24:41 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/11 23:00:52 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	parser_error(int type, int r_value)
{
	t_stringbuilder	*sb;
	char			*err_msg;

	sb = sb_create();
	if (r_value == 127)
		sb_append_str(sb, " line 2: command not found");
	else
		sb_append_str(sb, "syntax error: near unexpected token '");
	if (type == PIPE || type == AMPERSAND)
		sb_append_char(sb, type);
	else
	{
		if (type == OR)
			sb_append_str(sb, "||");
		else if (type == AND)
			sb_append_str(sb, "&&");
	}
	if (r_value != 127)
		sb_append_str(sb, "'");
	err_msg = sb_get_str(sb);
	sb_destroy(sb);
	error_msg(err_msg, r_value);
	free(err_msg);
	return (r_value);
}

static void	define_node(t_node *node, t_table **new)
{
	if (valid_name(&node->tokens) == SUCCESS)
	{
		if (check_redir(node->type))
			redir_parser(node->tokens, new);
		else if (node->type == COMMAND)
			command_parser(node->tokens, new);
	}
	else
		g_exit_status = error_msg("syntax error: unclosed quotes", FAIL);
}

static void	create_cmd_table(t_node **node, t_table **table) // TODO: error if LOG_OP consecutively and if LOG_OP not PIPE
{
	t_node	*curr_n;
	t_table	*new;

	curr_n = *node;
	while (curr_n)
	{
		new = append_table(table, new_table());
		if (check_log_op(curr_n->type))
		{
			new->log_op = curr_n->type;
			curr_n = curr_n->next;
			continue ;
		}
		while (curr_n && !check_log_op(curr_n->type))
		{
			define_node(curr_n, &new);
			curr_n = curr_n->next;
		}
	}
}

static bool	check_valid_first_token(t_type type)
{
	if (type == PIPE || type == AMPERSAND || type == OR || type == AND)
		return (false);
	return (true);
}

int	parser(t_node **node, t_table **table)
{
	if (!check_valid_first_token((*node)->type))
		g_exit_status = parser_error((*node)->type, 258);
	if (!(*node)->prev && !(*node)->next
		&& (!ft_strcmp((*node)->tokens->name, "\"\"")
			|| !ft_strcmp((*node)->tokens->name, "\'\'")
			|| !ft_strcmp((*node)->tokens->name, "\".\"")
			|| !ft_strcmp((*node)->tokens->name, "\'.\'")))
		g_exit_status = parser_error((*node)->type, 127);
	if (g_exit_status == SUCCESS)
		create_cmd_table(node, table);
	return (g_exit_status);
}
