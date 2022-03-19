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

#include "../include/minishell.h"

// TODO: call append_strn instead! 
static void	get_quoted_word(t_stringbuilder **sb, char **input)
{
	char	quote;

	quote = **input;
	sb_append_char(*sb, **input);
	(*input)++;
	while (**input && **input != quote)
	{
		sb_append_char(*sb, **input);
		(*input)++;
	}
	sb_append_char(*sb, **input);
}

char	*get_word(char **input)
{
	t_stringbuilder	*sb;
	char			*res;

	sb = sb_create();
	while (**input && !check_whitespace(**input) && !check_metachar(**input))
	{
		if (check_quotes(**input))
			get_quoted_word(&sb, input);
		else
			sb_append_char(sb, **input);
		(*input)++;
	}
	res = sb_get_str(sb);
	sb_destroy(sb);
	return (res);
}

char	*get_word_ws(char **input) // TODO: delete this func!! and change other references to new func
{
	int		i;
	int		size;
	char	*res;

	size = 0;
	while ((*input)[size] && !check_whitespace((*input)[size])
		&& !check_metachar((*input)[size]))
		size++;
	res = ft_calloc(size + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = (*input)[i];
		i++;
	}
	(*input) += i;
	return (res);
}