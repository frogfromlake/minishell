/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:35:16 by fquist            #+#    #+#             */
/*   Updated: 2022/03/13 16:53:20 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static	t_env *check_var_existence(t_env **env, char *args)
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

void	ft_export(t_table *table)
{
	t_env	**env;
	t_env	*tmp;
	t_env	*existing;
	int		ascii;

	ascii = 65;
	env = get_env(NULL);
	tmp = *env;
	if (!table->args)
	{
		while (ascii < 123)
		{
			tmp = *env;
			while (tmp)
			{
				if (tmp->var[0] == ascii)
					printf("%s\n", tmp->var);
				tmp = tmp->next;
			}
			ascii++;
		}
	}
	else
	{
		if (ft_strchr(table->args, '=') && table->args[0] != '=')
		{
			existing = check_var_existence(env, table->args);
			if (!existing)
				append_env(env, new_env(table->args));
			else
				ft_strcpy(existing->var, table->args);
		}
	}
}
