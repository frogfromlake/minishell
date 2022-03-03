/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelix <nelix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:37:24 by fquist            #+#    #+#             */
/*   Updated: 2022/03/03 03:59:19 by nelix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cd(t_table **table, t_env **env)
{
	t_table	*cmd;
	t_env	*curr_env;
	char	*home;

	cmd = *table;
	curr_env = *env;
	while (curr_env)
	{
		if (!ft_strncmp(curr_env->var, "HOME", 4))
			home = ft_strchr(curr_env->var, '/');
		curr_env = curr_env->next;
	}
	if (cmd->args)
		chdir(cmd->args);
	else if (!cmd->args || !ft_strcmp(cmd->args, "~"))
	{
		chdir(home);
	}
}
