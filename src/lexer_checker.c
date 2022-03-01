/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:13:39 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/01 15:56:54 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (true);
	return (false);
}

bool	check_metachar(char c)
{
	if (c == PIPE || c == AMPERSAND
		|| c == LESS || c == GREAT
		|| c == LPAREN || c == RPAREN)
		return (true);
	return (false);
}

bool	check_quotes(char c)
{
	if (c == SQUOTE || c == DQUOTE)
		return (true);
	return (false);
}

bool	check_redir(t_type type)
{
	if (type == LESS || type == GREAT || type == LESSLESS || type == GREATGREAT)
		return (true);
	return (false);
}
