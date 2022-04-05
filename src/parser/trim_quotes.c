/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:02:19 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/31 21:53:57 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void rm_dollar(char **str)
{
	t_stringbuilder	*sb;

	if (**str == '$' && (*(*str + 1) == DQUOTE || *(*str + 1) == SQUOTE))
	{
		sb = sb_create();
		sb_append_str(sb, (*str + 1));
		free(*str);
		*str = sb_get_str(sb);
		sb_destroy(sb);
	}
}

static void	get_word_trim(t_stringbuilder **sb, char **str)
{
	char	quote;
	int		i;

	quote = (**str);
	(*str)++;
	i = 0;
	while ((*str)[i] && (*str)[i] != quote)
		i++;
	sb_append_strn(*sb, *str, i);
	*(str) += (i + 1);
}

static void	get_quoted_word(t_token **token)
{
	t_stringbuilder	*sb;
	char			*tmp;

	sb = sb_create();
	tmp = (*token)->name;
	while (*tmp)
	{
		if (*tmp == SQUOTE || *tmp == DQUOTE)
		{
			get_word_trim(&sb, &tmp);
			continue ;
		}
		sb_append_char(sb, *tmp);
		tmp++;
	}
	free((*token)->name);
	(*token)->name = sb_get_str(sb);
	sb_destroy(sb);
}

void	trim_quotes(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (ft_strchr(tmp->name, SQUOTE) || ft_strchr(tmp->name, DQUOTE))
		{
			if (tmp->prev && tmp->prev->type == LESSLESS)
			{
				rm_dollar(&tmp->name);
				tmp->prev->type++;
			}
			get_quoted_word(&tmp);
		}
		tmp = tmp->next;
	}
}
