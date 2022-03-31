/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:02:45 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/12 18:32:59 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	get_quoted_word(t_stringbuilder **sb, char **input)
{
	int		i;
	char	quote;
	int		extra;

	quote = **input;
	extra = 0;
	i = 1;
	while ((*input)[i] && (*input)[i] != quote)
		i++;
	if ((*input)[i] == quote)
		extra++;
	sb_append_strn(*sb, *input, i + extra);
	(*input) += i;
}

char	*get_word(char **input)
{
	t_stringbuilder	*sb;
	char			*res;

	sb = sb_create();
	while (**input && !check_whitespace(**input) && !check_metachar(**input))
	{
		if (check_quotes(**input))
		{
			get_quoted_word(&sb, input);
			if (!(**input))
				break ;
		}
		else
			sb_append_char(sb, **input);
		(*input)++;
	}
	res = sb_get_str(sb);
	sb_destroy(sb);
	return (res);
}
