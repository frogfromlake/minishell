/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:24:41 by dmontema          #+#    #+#             */
/*   Updated: 2022/02/28 17:17:49 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_node **commands)
{
	t_token	*token;

	token = (*commands)->args;
	while (token)
	{
		printf("%s\n", token->cmd);
		token = token->next;
	}
	return (0);
}

void	echo_tokens(t_token *token)
{
	while (token)
}