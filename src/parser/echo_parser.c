/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 03:09:51 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/27 23:08:57 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_quoted_word(char *str, t_stringbuilder **sb)
{
	char	quote;
	int		i;

	i = 0;
	quote = str[i++];
	while (str[i] != quote)
	{
		sb_append_char(*sb, str[i]);
		i++;
	}
	return (++i);
}

static bool	check_valid_opt(char *opt)
{
	int	i;

	i = 0;
	if (ft_strncmp(opt, "-n", 2))
		return (false);
	i += 2;
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static bool	check_opt(t_token **token)
{
	if (!check_valid_opt((*token)->name) || !(*(*token)->name))
		return (false);
	while (*token)
	{
		if ((*token)->type == NONEXISTENV)
		{
			(*token) = (*token)->next;
			continue ;
		}
		if (!check_valid_opt((*token)->name))
			break ;
		(*token) = (*token)->next;
	}
	return (true);
}

int	define_echo_args(t_token *token, t_table **new)
{
	t_stringbuilder	*sb;
	int				opt;

	opt = 0;
	if (check_opt(&token))
		opt = 1;
	if (!token)
		return (opt);
	sb = sb_create();
	while (token)
	{
		if (check_quotes(*token->name))
			get_quoted_word(token->name, &sb);
		else
			sb_append_str(sb, token->name);
		if (token->next)
			sb_append_char(sb, ' ');
		token = token->next;
	}
	(*new)->args = sb_get_str(sb);
	sb_destroy(sb);
	g_exit_status = SUCCESS;
	return (opt);
}
