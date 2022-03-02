/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:37:24 by fquist            #+#    #+#             */
/*   Updated: 2022/03/02 04:32:24 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
