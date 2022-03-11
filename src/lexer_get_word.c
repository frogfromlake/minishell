/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:02:45 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/11 23:07:15 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char	*get_word_redir(t_type type, char **input)
{
	int		i;
	int		size;
	bool	redir;
	char	*res;

	if (type == LESS || type == GREAT)
		size = 3;
	else
		size = 4;
	while ((*input)[size] && !check_whitespace((*input)[size]))
		size++;
	res = ft_calloc(size + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	redir = false;
	while (!redir || ((*input)[i] && !check_whitespace((*input)[i])))
	{
		if (check_whitespace((*input)[i]) || !check_redir((*input)[i]))
			redir = true;
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
	char	quote;

	quote = **input;
	size = 1;
	while ((*input)[size] && (*input)[size] != quote)
		size++;
	res = ft_calloc(++size + 1, sizeof(char));
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
