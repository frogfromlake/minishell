/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:35:21 by fquist            #+#    #+#             */
/*   Updated: 2022/02/26 21:50:40 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_node **node)
{
	t_token	*token;

	token = (*node)->args;
	if (!ft_strcmp(token->cmd, "exit"))
	{
		write(1, "logout\n", 8);
		exit(EXIT_SUCCESS);
	}
}
