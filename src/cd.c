/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:37:24 by fquist            #+#    #+#             */
/*   Updated: 2022/03/11 00:32:49 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TODO: change env_var PWD after changing directory

void	ft_cd(t_table *table)
{
	t_env	*curr_env;
	char	*home;

	curr_env = *(get_env(NULL));
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
