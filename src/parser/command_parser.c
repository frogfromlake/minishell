/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:39:49 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/31 19:22:48 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	add_args(t_token *token, t_table **new)
{
	if (!ft_strcmp((*new)->exe, "cd"))
		(*new)->args = ft_strdup(token->name);
	else
		add_args_to_arr(token, new);
}

static int	cmd_parser_error(char *str, int r_value)
{
	t_stringbuilder	*sb;
	char			*err_msg;

	sb = sb_create();
	sb_append_str(sb, "command not found: ");
	sb_append_str(sb, str);
	err_msg = sb_get_str(sb);
	sb_destroy(sb);
	error_msg(err_msg, r_value);
	free(err_msg);
	return (r_value);
}

static void	nonbuiltin_parser(t_token *token, t_table **new)
{
	g_exit_status = set_cmd_path(new);
	if (g_exit_status)
		cmd_parser_error((*new)->exe, g_exit_status);
	else
	{
		if (token->next)
			add_args_to_arr(token->next, new);
		g_exit_status = SUCCESS;
	}
}

int	command_parser(t_token *token, t_table **new)
{
	if ((*new)->exe)
		free((*new)->exe);
	(*new)->exe = ft_strdup(token->name);
	if (!check_builtin(*new))
		nonbuiltin_parser(token, new);
	else if (!ft_strcmp_upper_lower((*new)->exe, "echo"))
	{
		if (token->next)
			if (define_echo_args(token->next, new))
				(*new)->opt = 1;
	}
	else
	{
		if (token->next)
			add_args(token->next, new);
		g_exit_status = SUCCESS;
	}
	return (g_exit_status);
}
