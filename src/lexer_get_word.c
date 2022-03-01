/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:02:45 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/01 20:06:47 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word_args(char **input)
{
	int		i;
	int		size;
	char	*res;

	size = 0;
	while ((*input)[size] && !check_metachar((*input)[size]))
		size++;
	res = ft_calloc(size + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while ((*input)[i] &&
		!check_metachar((*input)[i]) && !check_quotes((*input)[i]))
	{
		res[i] = (*input)[i];
		i++;
	}
	(*input) += i;
	return (res);
}

char	*get_word_ws(char **input)
{
	int		i;
	int		size;
	char	*res;

	size = 0;
	while ((*input)[size] && !check_whitespace((*input)[size]))
		size++;
	res = ft_calloc(size + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while ((*input)[i] && !check_whitespace((*input)[i]))
	{
		res[i] = (*input)[i];
		i++;
	}
	(*input) += i;
	return (res);
}

char	*get_word_quoted(char **input)
{
	int		i;
	int		size;
	char	*res;

	size = 1;
	while ((*input)[size] && !check_quotes((*input)[size]))
		size++;
	res = ft_calloc(++size, sizeof(char));
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
