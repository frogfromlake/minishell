/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:52:05 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/20 18:52:05 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	check_quotes_closed(char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	while (**str)
	{
		if (**str == quote)
		{
			(*str)++;
			return (true);
		}
		(*str)++;
	}
	return (false);
}

int	valid_name(t_token *token)
{
	char	*name;

	while (token)
	{
		if (ft_strchr(token->name, SQUOTE) || ft_strchr(token->name, DQUOTE))
		{
			name = token->name;
			while (*name)
			{
				if (*name == SQUOTE || *name == DQUOTE)
				{
					if (!check_quotes_closed(&name))
						return (FAIL); //FAIL!
					continue ;
				}
				name++;
			}
		}
		token = token->next;
	}
	return (SUCCESS); // SUCCESS!
}