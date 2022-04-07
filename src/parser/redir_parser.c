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
		if (!ft_strcmp(redir, "<"))
			return (true);
	}
	if (type == LESSLESS || type == LESSLESS + 1)
	{
		if (!ft_strcmp(redir, "<<"))
			return (true);
	}
	if (type == GREAT)
	{
		if (!ft_strcmp(redir, ">"))
			return (true);
	}
	if (type == GREATGREAT)
	{
		if (!ft_strcmp(redir, ">>"))
			return (true);
	}
	return (false);
}

int	redir_parser(t_token **token, t_table **new)
{
	t_type	type;
	char	*name;

	if (!check_valid_redir((*token)->name, (*token)->type))
		return (redir_parser_error((*token)->name, 2));
	type = (*token)->type;
	if (!(*token)->next)
		return (redir_parser_error(NULL, 2));
	(*token) = (*token)->next;
	if (check_redir((*token)->name[0])
		|| check_redir((*token)->name[ft_strlen((*token)->name) - 1]))
		return (redir_parser_error((*token)->name, 2));
	name = ft_strdup((*token)->name);
	append_redir(&(*new)->redir, new_redir(type, name));
	g_exit_status = SUCCESS;
	(*token) = (*token)->next;
	return (g_exit_status);
}
