/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 22:47:42 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/11 00:31:29 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_env_size(t_env *env)
{
	int	res;

	res = 0;
	env = *(get_env(NULL));
	while (env)
	{
		res++;
		env = env->next;
	}
	return (res);
}

char	**get_env_arr(void)
{
	int		i;
	t_env	*tmp;
	char	**env_arr;

	tmp = *(get_env(NULL));
	env_arr = ft_calloc(get_env_size(tmp) + 1, sizeof(char *));
	i = 0;
	while (tmp)
	{
		env_arr[i] = ft_strdup(tmp->var);
		i++;
		tmp = tmp->next;
	}
	return (env_arr);
}

static char	*get_var_name(t_env *env)
{
	t_stringbuilder	*sb;
	int				i;
	char			*res;

	sb = sb_create();
	i = 0;
	while (env->var[i] != '=')
		i++;
	sb_append_strn(sb, env->var, i);
	res = sb_get_str(sb);
	sb_destroy(sb);
	return (res);
}

char	*get_env_var(char *str)
{
	t_env	*env;
	char	*var_name;

	env = *get_env(NULL);
	while (env)
	{
		var_name = get_var_name(env);
		if (!ft_strcmp(var_name, str))
		{
			free(var_name);
			return (ft_strchr(env->var, '=') + 1);
		}
		free(var_name);
		env = env->next;
	}
	return (NULL);
}
