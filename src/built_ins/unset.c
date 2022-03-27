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

static bool	check_valid_arg(char *str)
{
	if (!ft_is_alpha(*str) && *str != '_')
		return (false);
	str++;
	while (*str)
	{
		if (!ft_is_all_num(*str) && *str == '_')
			return (false);
		str++;
	}
	return (true);
}

void	ft_unset(t_table *table)
{
	t_env	*curr_env;
	t_env	*prev;
	char	*tmp;

	curr_env = *(get_env(NULL));
	prev = curr_env;
	if (check_valid_arg(table->args))
	{
		while (curr_env)
		{
			tmp = get_var_name(curr_env);
			if (!ft_strcmp(tmp, table->args))
			{
				prev->next = curr_env->next;
				free(curr_env->var);
				curr_env->var = NULL;
				free(curr_env);
				curr_env = NULL;
				break ;
			}
			if (tmp)
				free(tmp);
			prev = curr_env;
			curr_env = curr_env->next;
		}
	}
	else
		g_exit_status = error_msg("minishell: unset: 'arg': "
				"not a valid identifier\n", FAIL);
}
