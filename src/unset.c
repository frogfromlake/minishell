/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelix <nelix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:24:35 by fquist            #+#    #+#             */
/*   Updated: 2022/03/03 04:00:40 by nelix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
