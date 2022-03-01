/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:37:24 by fquist            #+#    #+#             */
/*   Updated: 2022/03/01 14:24:14 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_table **table, char **environ)
{
	t_table	*cmd;
	char	*home;
	int		i;

	cmd = *table;
	i = 0;
	printf("%s\n", cmd->args);
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], "HOME", 4))
			home = ft_strchr(environ[i], '/');
		i++;
	}
	if (!cmd->args || !ft_strcmp(cmd->args, "~"))
		chdir(home);
	else
		chdir(cmd->args);
}
