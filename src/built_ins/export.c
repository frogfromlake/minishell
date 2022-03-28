/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:35:16 by fquist            #+#    #+#             */
/*   Updated: 2022/03/29 00:09:55 by dmontema         ###   ########.fr       */
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

static char	*get_args_var_name(char *args)
{
	t_stringbuilder	*sb;
	int				i;
	char			*res;

	sb = sb_create();
	i = 0;
	while (args[i])
	{
		if (args[i] == '=')
			break ;
		i++;
	}
	sb_append_strn(sb, args, i);
	res = sb_get_str(sb);
	sb_destroy(sb);
	return (res);
}

static t_env	*check_var_existence(t_env **env, char *args)
{
	t_env	*tmp;
	char	*var_name;
	char	*args_var_name;

	tmp = *env;
	while (tmp)
	{
		var_name = get_var_name(tmp);
		args_var_name = get_args_var_name(args);
		if (!ft_strcmp(var_name, args_var_name))
		{
			free(args_var_name);
			free(var_name);
			return (tmp);
		}
		free(args_var_name);
		free(var_name);
		tmp = tmp->next;
	}
	return (NULL);
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

void	ft_export(char *args)
{
	t_env	**env;
	t_env	*existing;
	char	**split_args;
	int		i;

	env = get_env(NULL);
	if (!args)
		print_env_vars(*env);
	else
	{
		split_args = ft_split(args, ' ');
		i = 0;
		while (split_args[i])
		{
			if (check_valid_var(&split_args[i]))
			{
				existing = check_var_existence(env, split_args[i]);
				if (!existing)
					append_env(env, new_env(split_args[i]));
				else
				{
					free(existing->var);
					existing->var = ft_strdup(split_args[i]);
				}
			}
			else
				g_exit_status = export_error(split_args[i], FAIL);
			i++;
		}
		ft_free_split(split_args);
	}
}
