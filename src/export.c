/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:35:16 by fquist            #+#    #+#             */
/*   Updated: 2022/03/01 23:25:04 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_env **env, t_table *table)
{
	t_env	*tmp;
	int		ascii;

	ascii = 65;
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
			while (tmp)
			{
				if (!ft_strncmp(tmp->var, "_=", 2))
					insert_env(&tmp, new_env(table->args));
				tmp = tmp->next;
			}
		}
	}
}
