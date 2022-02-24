/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:40:37 by fquist            #+#    #+#             */
/*   Updated: 2022/02/24 20:31:04 by dmontema         ###   ########.fr       */
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

char	*get_word(char **input, int cmd, int opt)
{
	int		i;
	int		size;
	char	*res;

	size = 0;
	while ((*input)[size] && !is_pipe_or_sth((*input)[size]))
		size++;
	res = ft_calloc(size + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	if (!cmd || opt == 1)
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
		while (**input && !is_pipe_or_sth(**input))
		{
			res[i] = **input;
			i++;
			(*input)++;
		}

	}
	return (res);
}

int	create_tokens(t_node **node, char **input)
{
	t_token	*new;
	int		opt;
	int		cmd_present;

	cmd_present = 0;
	while(**input && !is_pipe_or_sth(**input))
	{
		opt = 0;
		if (**input == '-')
			opt++;
		new = new_token(get_word(input, cmd_present++, opt));
		if (new->cmd[0] == '-')
			new->is_option = 1;
		// new = append_token(&(*node)->args, new_token(get_word(input, cmd_present)));
		// cmd_present++;
		append_token(&(*node)->args, new);
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
			create_tokens(&new, &input);
	}
	return (1);
}