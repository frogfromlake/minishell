/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:35:16 by fquist            #+#    #+#             */
/*   Updated: 2022/03/30 02:57:32 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	export_error(char *str, int r_value)
{
	t_stringbuilder	*sb;
	char			*err_msg;

	sb = sb_create();
	sb_append_str(sb, "export: '");
	sb_append_str(sb, str);
	sb_append_str(sb, "': not a valid identifier");
	err_msg = sb_get_str(sb);
	sb_destroy(sb);
	error_msg(err_msg, r_value);
	free(err_msg);
	return (r_value);
}

static void	add_env_var(t_table *table, t_env **env)
{
	t_env	*existing;
	int		i;

	i = 0;
	while (table->cmd_arr[i])
	{
		if (check_valid_var(&table->cmd_arr[i]))
		{
			existing = check_var_existence(env, table->cmd_arr[i]);
			if (!existing)
				append_env(env, new_env(table->cmd_arr[i]));
			else
			{
				free(existing->var);
				existing->var = ft_strdup(table->cmd_arr[i]);
			}
		}
		else
			g_exit_status = export_error(table->cmd_arr[i], FAIL);
		i++;
	}
}

static void	print_env_vars(t_env *env)
{
	t_env	*tmp;
	int		ascii;

	ascii = 65;
	while (ascii < 123)
	{
		tmp = env;
		while (tmp)
		{
			if (tmp->var[0] == ascii)
				printf("declare -x %s\n", tmp->var);
			tmp = tmp->next;
		}
		ascii++;
	}
}

void	ft_export(t_table *table)
{
	t_env	**env;

	env = get_env(NULL);
	if (!table->args)
		print_env_vars(*env);
	else if (!*table->args)
	{
		g_exit_status = error_msg("export: not a valid identifier", FAIL);
		return ;
	}
	else
		add_env_var(table, env);
}
