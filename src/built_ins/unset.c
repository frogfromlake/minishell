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

void	ft_unset(t_table *table)
{
	t_env	*curr_env;
	t_env	*prev;
	char	*tmp;
	int		i;

	g_exit_status = 0;
	if (!table->args)
		return ;
	if (!*table->args)
	{
		g_exit_status = error_msg("line 2: unset: `': not a valid identifier", FAIL);
		return ;
	}
	i = 0;
	while (table->cmd_arr[i])
	{
		curr_env = *(get_env(NULL));
		prev = curr_env;
		if (check_valid_arg(table->cmd_arr[i]))
		{
			while (curr_env)
			{
				tmp = get_var_name(curr_env);
				if (!ft_strcmp(tmp, table->cmd_arr[i]))
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
			g_exit_status = unset_error(table->cmd_arr[i], FAIL);
		i++;
	}
}
