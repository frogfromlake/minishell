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

int	redir_parser(t_token *curr_t, t_table **new)
{
	t_type	type;
	char	*filename;

	if (*curr_t->name != 0)
	{
		type = curr_t->type;
		filename = ft_strdup(curr_t->name);
		append_redir(&(*new)->redir, new_redir(type, filename));
		g_exit_status = SUCCESS;
	}
	else
		g_exit_status = error_msg("syntax error near unexpected token", 2);
	return (g_exit_status);
}

// static int	redir_parser_error(char *str, int r_value)
// {
// 	t_stringbuilder	*sb;
// 	char			*err_msg;

// 	sb = sb_create();
// 	if (str)
// 	{
// 		sb_append_str(sb, "syntax error: near unexpected token '");
// 		sb_append_str(sb, str);
// 		sb_append_char(sb, SQUOTE);
// 	}
// 	else
// 		sb_append_str(sb, "syntax error");
// 	err_msg = sb_get_str(sb);
// 	sb_destroy(sb);
// 	error_msg(err_msg, r_value);
// 	free(err_msg);
// 	return (r_value);
// }

// static check_valid_redir(char *redir)
// {
// 	(void) redir;
// 	return (false);
// }

// int redir_parser(t_token **token, t_table **new)
// {
// 	t_type	type;
// 	char	*name;

// 	if (!check_valid_redir((*token)->name))
// 		return (redir_parser_error((*token)->name, FAIL));
// 	type = (*token)->type;
// 	if (!(*token)->next)
// 		return (redir_parser_error(NULL, FAIL));
// 	(*token) = (*token)->next;
// 	name = ft_strdup((*token)->name);
// 	append_redir(&(*new)->redir, new_redir(type, filename));
// 	g_exit_status = SUCCESS;
// 	(*token) = (*token)->next;
// 	return (g_exit_status);
// }
