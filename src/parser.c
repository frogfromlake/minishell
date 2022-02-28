/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:24:41 by dmontema          #+#    #+#             */
/*   Updated: 2022/02/28 18:01:43 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_node **commands)
{
	t_token	*token;
	t_table	*element;

	token = (*commands)->args;
	while (token)
	{
		printf("%s\n", token->cmd);
		if (token->type == GREAT || token->type == LESS)

		token = token->next;
	}
	return (0);
}

