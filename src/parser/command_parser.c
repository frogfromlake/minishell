/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:39:49 by dmontema          #+#    #+#             */
/*   Updated: 2022/04/04 14:52:27 by dmontema         ###   ########.fr       */
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

int	command_parser(t_token **token, t_table **new)
{
	(*new)->exe = ft_strdup((*token)->name);
	g_exit_status = SUCCESS;
	if (!check_builtin(*new))
		g_exit_status = set_cmd_path(new);
	if (g_exit_status)
		cmd_parser_error((*new)->exe, g_exit_status);
	(*token) = (*token)->next;
	return (g_exit_status);
}
