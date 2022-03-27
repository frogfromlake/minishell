/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:35:16 by fquist            #+#    #+#             */
/*   Updated: 2022/03/27 01:32:48 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
				// ft_strcpy(existing->var, args);
			}
		}
	}
}
