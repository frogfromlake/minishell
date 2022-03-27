/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:35:16 by fquist            #+#    #+#             */
/*   Updated: 2022/03/27 21:23:38 by dmontema         ###   ########.fr       */
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

static int	equal_strlen(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

static t_env	*check_var_existence(t_env **env, char *args)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, args, equal_strlen(args)))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
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

	env = get_env(NULL);
	if (!args)
		print_env_vars(*env);
	else
	{
		if (check_valid_var(&args))
		{
			existing = check_var_existence(env, args);
			if (!existing)
				append_env(env, new_env(args));
			else
			{
				free(existing->var);
				existing->var = ft_strdup(args);
			}
		}
		else
			export_error(args, FAIL);
	}
}
