/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 03:59:54 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/03 23:38:20 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	redir_parser_error(char *str, int r_value)
{
	t_stringbuilder	*sb;
	char			*err_msg;

	sb = sb_create();
	if (str)
	{
		sb_append_str(sb, "syntax error: near unexpected token '");
		sb_append_str(sb, str);
		sb_append_char(sb, SQUOTE);
	}
	else
		sb_append_str(sb, "syntax error");
	err_msg = sb_get_str(sb);
	sb_destroy(sb);
	error_msg(err_msg, r_value);
	free(err_msg);
	return (r_value);
}

static bool	check_valid_redir(char *redir, t_type type)
{
	if (type == LESS)
	{
		if (redir[0] == LESS && !redir[1])
			return (true);
	}
	if (type == LESSLESS || type == LESSLESS + 1)
	{
		if (redir[0] == LESS && redir[1] == LESS && !redir[2])
			return (true);
	}
	if (type == GREAT)
	{
		if (redir[0] == GREAT && !redir[1])
			return (true);
	}
	if (type == GREATGREAT)
	{
		if (redir[0] == GREAT && redir[1] == GREAT && !redir[2])
			return (true);
	}
	return (false);
}

int	redir_parser(t_token **token, t_table **new)
{
	t_type	type;
	char	*name;

	if (!check_valid_redir((*token)->name, (*token)->type))
		return (redir_parser_error((*token)->name, FAIL));
	type = (*token)->type;
	if (!(*token)->next)
		return (redir_parser_error(NULL, FAIL));
	(*token) = (*token)->next;
	name = ft_strdup((*token)->name);
	append_redir(&(*new)->redir, new_redir(type, name));
	g_exit_status = SUCCESS;
	(*token) = (*token)->next;
	return (g_exit_status);
}
