/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:37:24 by fquist            #+#    #+#             */
/*   Updated: 2022/03/10 16:21:30 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cd(t_table *table, t_env **env)
{
	t_env	*curr_env;
	char	*home;

	curr_env = *env;
	while (curr_env)
	{
		if (!ft_strncmp(curr_env->var, "HOME", 4))
			home = ft_strchr(curr_env->var, '/');
		curr_env = curr_env->next;
	}
	if (table->args)
		chdir(table->args);
	else if (!table->args || !ft_strcmp(table->args, "~"))
		chdir(home);
}
