/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:47:19 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/12 01:24:13 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	check_quotes_closed(char *str)
{
	char quote;
	int	last;

	quote = *str;
	last = ft_strlen(str) - 1;
	if (str[last] == quote)
		return (true);
	return (false);
}

int	expander(t_node **node)
{
	t_node	*curr;
	t_token	*token;
	char	quote;
	char	*tmp;

	curr = *node;
	while (curr)
	{
		if (!check_log_op(curr->type))
		{
			if (curr->tokens)
			{
				token = curr->tokens;
				while (token)
				{
					// handle case with here_doc redir - TODO: maybe do this on the lexer
					if (token->type == LESSLESS && check_quotes(*token->name) && check_quotes_closed(token->name))
					{
						quote = *token->name;
						tmp = token->name;
						token->name = ft_strtrim(token->name, &quote);
						free(tmp);
						printf("|%s|\n", token->name);
					}
					else if (check_quotes(*token->name) && *token->name == '\'' && check_quotes_closed(token->name)) // trim single quotes.
					{
						quote = *token->name;
						tmp = token->name;
						token->name = ft_strtrim(token->name, &quote);
						free(tmp);
					}
					token = token->next;
				}
			}
		}
		curr = curr->next;
	}
	printf("\n");
	return (1);
}