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

#include "../include/minishell.h"

int		get_env_size(t_env *env)
{
	int		res;

	res = 0;
	env = *(get_env(NULL));
	while (env)
	{
		res++;
		env = env->next;
	}
	return (res);
}

char	**get_env_arr() // TODO: free from where it is called.
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

char	*get_env_var(char *str)
{
	t_env	*env;

	env = *get_env(NULL);
	while (env)
	{
		if (!ft_strncmp(env->var, str, ft_strlen(str)))
		{
			return (ft_strchr(env->var, '=') + 1);
		}
		env = env->next;
	}
	return (NULL);
}
