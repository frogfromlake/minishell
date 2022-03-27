/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:52:05 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/27 00:00:57 by fquist           ###   ########.fr       */
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

int	valid_name(t_token **token)
{
	t_token	*tmp;
	char	*name;

	tmp = *token;
	while (tmp)
	{
		if (ft_strchr(tmp->name, SQUOTE) || ft_strchr(tmp->name, DQUOTE))
		{
			name = tmp->name;
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
		tmp = tmp->next;
	}
	trim_quotes(token);
	return (SUCCESS); // SUCCESS!
}

int	error_msg(char *error_msg, int r_value)
{
	ft_putstr_fd(error_msg, 2);
	return (r_value);
}
