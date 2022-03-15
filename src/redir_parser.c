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

#include "../include/minishell.h"

// TODO: error handling, change name of check_redir_quotes

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

static bool	check_quotes_closed(char *str, t_stringbuilder **sb)
{
	char	quote;

	quote = *str;
	while (*str)
	{
		if (*str == quote)
			return (true);
		str++;
	}
	sb_destroy(*sb);
	return (false);
}

static int	check_redir_quotes(char *str, char **filename)
{
	t_stringbuilder	*sb;
	int				i;
	int				ret;

	sb = sb_create();
	i = 0;
	ret = 0;
	while (str[i])
	{
		if (check_quotes(str[i]))
		{
			ret = 1;
			if (!check_quotes_closed(&str[i], &sb))
				return (-1);
			i += get_quoted_word(&str[i], &sb);
		}
		else
		{
			sb_append_char(sb, str[i]);
			i++;
		}
	}
	*filename = sb_get_str(sb);
	sb_destroy(sb);
	return (ret);
}

int	redir_parser(t_token *curr_t, t_table **new)
{
	t_type	type;
	char	*filename;

	type = curr_t->type;
	filename = NULL;
	if (check_redir_quotes(curr_t->name, &filename) == 1)
	{
		if (curr_t->type == LESSLESS)
			type++;
	}
	append_redir(&(*new)->redir, new_redir(type, filename));
	return (1);
}
