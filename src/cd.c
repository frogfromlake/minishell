/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:37:24 by fquist            #+#    #+#             */
/*   Updated: 2022/02/26 19:02:08 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_node **node)
{
	t_token	*token;

	token = (*node)->args;
	chdir(token->next->cmd);
	return ;
}
