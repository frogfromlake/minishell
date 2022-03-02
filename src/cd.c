/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:37:24 by fquist            #+#    #+#             */
/*   Updated: 2022/03/02 04:12:06 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//TODO: FIXME: change environ to env
void	ft_cd(t_table **table, char **environ)
{
	t_table	*cmd;
	char	*home;
	int		i;

	cmd = *table;
	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], "HOME", 4))
			home = ft_strchr(environ[i], '/');
		i++;
	}
	if (cmd->args)
		chdir(cmd->args);
	else if (!cmd->args || !ft_strcmp(cmd->args, "~"))
	{
		chdir(home);
	}
}
