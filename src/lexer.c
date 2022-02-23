/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:40:37 by fquist            #+#    #+#             */
/*   Updated: 2022/02/24 00:44:48 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_pipe_or_sth(int c)
{
	if (c == PIPE || c == AMPERSAND || c == LPAREN || c == RPAREN
		|| c == AND || c == OR)
		return (true);
	return (false);
}

char	*get_word(char **input)
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
	while (!check_whitespace(**input) && **input)
	{
		res[i] = **input;
		i++;
		(*input)++;
	}
	return (res);
}

int	create_tokens(t_node **node, char **input)
{
	t_token *new;

	while(**input && !is_pipe_or_sth(**input))
	{
		new = append_token(&(*node)->args, new_token(get_word(input)));
		while (check_whitespace(**input))
			(*input)++;
	}
	return (1);
}

int	define_type(char *input)
{
	if (input[0] == LPAREN || input[0] == RPAREN)
		return (input[0]);
	if (input[0] == PIPE || input[0] == AMPERSAND)
	{
		if (input[0] == input[1])
			return(input[0] * 4);
		else 
			return input[0];
	}
	return (COMMAND);
}

int	lexer(t_node **head, char *input)
{
	t_node	*new;

	while (*input)
	{
		if (check_whitespace(*input))
		{
			input++;
			continue ;
		}
		new = append_node(head, new_node());
		new->type = define_type(input);
		if (new->type == AND || new->type == OR)
			input += 2;
		else if (new->type != COMMAND)
			input++;
		else
		{
			//create tokens
			create_tokens(&new, &input);
			// while (!check_whitespace(*input) && *input)
			// 	input++;
		}
	}
	return (1);
}