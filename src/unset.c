/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:24:35 by fquist            #+#    #+#             */
/*   Updated: 2022/03/01 22:46:49 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_env **env, t_table *table) // TODO: error handling!
{
	t_env	*curr_env;
	t_env	*prev;

	curr_env = *env;
	prev = curr_env;
	while (curr_env)
	{
		if (!ft_strncmp(curr_env->var, table->args, ft_strlen(table->args)))
		{
			prev->next = curr_env->next;
			free(curr_env);
			curr_env = NULL;
			break ;
		}
		prev = curr_env;
		curr_env = curr_env->next;
	}
}
