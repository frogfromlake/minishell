/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:02:45 by dmontema          #+#    #+#             */
/*   Updated: 2022/02/28 20:53:24 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word(char **input, int name, int opt)
{
	int		i;
	int		size;
	char	*res;

	size = 0;
	while ((*input)[size] && !is_metachar((*input)[size]))
		size++;
	res = ft_calloc(size + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	if (!name || opt == 1)
	{
		while (**input && !check_whitespace(**input))
		{
			res[i] = **input;
			i++;
			(*input)++;
		}
	}
	else
	{
		while (**input && !is_metachar(**input) && !is_quoted(**input))
		{
			res[i] = **input;
			i++;
			(*input)++;
		}
	}
	return (res);
}

char	*get_quoted_word(char **input)
{
	int		i;
	int		size;
	char	*res;

	size = 1;
	while ((*input)[size] && !is_quoted((*input)[size]))
		size++;
	res = ft_calloc(++size, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (**input && i < size)
	{
		res[i] = **input;
		i++;
		(*input)++;
	}
	return (res);
}

bool	is_metachar(int c)
{
	if (c == PIPE || c == AMPERSAND || c == LESS || c == GREAT || c == LPAREN || c == RPAREN)
		return (true);
	return (false);
}

bool	is_quoted(char c)
{
	if (c == SQUOTE || c == DQUOTE)
		return (true);
	else
		return (false);
}
