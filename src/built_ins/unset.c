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

static int	unset_error(char *str, int r_value)
{
	t_stringbuilder	*sb;
	char			*err_msg;

	sb = sb_create();
	sb_append_str(sb, "unset: '");
	sb_append_str(sb, str);
	sb_append_str(sb, "': not a valid identifier");
	err_msg = sb_get_str(sb);
	sb_destroy(sb);
	error_msg(err_msg, r_value);
	free(err_msg);
	return (r_value);
}

static bool	check_valid_arg(char *str)
{
	if (!*str || (!ft_is_alpha(*str) && *str != '_'))
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

static void	rm_env_var(char *str, t_env	*curr_env, t_env *prev)
{
	char	*tmp;

	if (check_valid_arg(str))
	{
		while (curr_env)
		{
			tmp = get_var_name(curr_env);
			if (!ft_strcmp(tmp, str))
			{
				prev->next = curr_env->next;
				free(curr_env->var);
				curr_env->var = NULL;
				free(curr_env);
				curr_env = NULL;
				free(tmp);
				break ;
			}
			if (tmp)
				free(tmp);
			prev = curr_env;
			curr_env = curr_env->next;
		}
	}
	else
		g_exit_status = unset_error(str, FAIL);
}

void	ft_unset(t_table *table)
{
	t_env	*curr_env;
	int		i;

	g_exit_status = 0;
	if (!table->args)
		return ;
	if (!*table->args)
	{
		g_exit_status = error_msg("unset: not a valid identifier", FAIL);
		return ;
	}
	i = 0;
	curr_env = *(get_env(NULL));
	while (table->cmd_arr[i])
	{
		rm_env_var(table->cmd_arr[i], curr_env, curr_env);
		i++;
	}
}
