/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:24:35 by fquist            #+#    #+#             */
/*   Updated: 2022/03/11 00:36:52 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(t_table *table) // TODO: error handling!
{
	t_env	*curr_env;
	t_env	*prev;

	curr_env = *(get_env(NULL));
	prev = curr_env;
	while (curr_env)
	{
		if (!ft_strncmp(curr_env->var, table->args, ft_strlen(table->args)))
		{
			prev->next = curr_env->next;
			free(curr_env->var);
			curr_env->var = NULL;
			free(curr_env);
			curr_env = NULL;
			break ;
		}
		prev = curr_env;
		curr_env = curr_env->next;
	}
}
