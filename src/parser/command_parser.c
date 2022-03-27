/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:39:49 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/27 21:15:12 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	command_parser(t_token *token, t_table **new)
{
	(*new)->exe = ft_strdup(token->name);
	if (!check_builtin(*new))
	{
		g_exit_status = set_cmd_path(new, get_env(NULL));
		if (g_exit_status)
			cmd_parser_error((*new)->exe, g_exit_status);
		else
		{
			if (token->next)
				add_args_to_arr(token->next, new);
			g_exit_status = SUCCESS;
		}
	}
	else if (!ft_strcmp((*new)->exe, "echo"))
	{
		if (token->next)
			if (define_echo_args(token->next, new))
				(*new)->opt = 1;
	}
	else
	{
		if (token->next) // TODO: implement for more args (e.g. export can also set multiple args at once.)
			(*new)->args = ft_strdup(token->next->name);
		g_exit_status = SUCCESS;
	}
	return (g_exit_status);
}
