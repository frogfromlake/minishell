/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:40:37 by fquist            #+#    #+#             */
/*   Updated: 2022/02/26 20:12:42 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_redir_token(t_node **node, char **input)
{
	while (**input == LESS || **input == GREAT
		|| check_whitespace(**input))
		(*input)++;
	append_token(&(*node)->args, new_token(get_word(input, 0, 0)));
	return (1);
}

int	create_tokens(t_node **node, char **input)
{
	t_token	*new;
	int		opt;
	int		cmd_present;

	if ((*node)->type == LESS || (*node)->type == LESSLESS
		|| (*node)->type == GREAT || (*node)->type == GREATGREAT)
		create_redir_token(node, input);
	else
	{
		cmd_present = 0;
		while ((**input && !is_metachar(**input)))
		{
			opt = 0;
			if (**input == '-')
				opt++;
			if (is_quoted(**input))
				new = new_token(get_quoted_word(input));
			else
				new = new_token(get_word(input, cmd_present++, opt));
			if (new->cmd[0] == '-')
				new->is_option = 1;
			append_token(&(*node)->args, new);
			while (check_whitespace(**input))
				(*input)++;
		}
	}
	return (1);
}

int	define_type(char *input)
{
	if (input[0] == LPAREN || input[0] == RPAREN)
		return (input[0]);
	if (input[0] == PIPE || input[0] == AMPERSAND
		|| input[0] == LESS || input[0] == GREAT)
	{
		if (input[0] == input[1])
			return (input[0] * 4);
		else
			return (input[0]);
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
		else if (new->type == COMMAND || new->type == LESS || new->type == GREAT
			|| new->type == LESSLESS || new->type == GREATGREAT)
			create_tokens(&new, &input);
		else
			input++;
	}
	return (1);
}
