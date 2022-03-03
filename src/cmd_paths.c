/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:50:10 by fquist            #+#    #+#             */
/*   Updated: 2022/03/03 23:42:19 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_cmd_path(t_table **table)
{
	int		i;
	char	*tmp;
	char	**cmd_paths;

	i = 0;
	if (access((*table)->exe, F_OK) == 0)
		return (0);
	cmd_paths = get_env_path();
	if (cmd_paths == NULL)
		return (ENOMEM);
	while (cmd_paths[i])
	{
		tmp = ft_strjoin(cmd_paths[i], (*table)->exe);
		if (access(tmp, F_OK) == 0)
		{
			(*table)->exe = tmp;
			ft_free_split(cmd_paths);
			return (0);
		}
		free(tmp);
		i++;
	}
	ft_free_split(cmd_paths);
	return (127);
}

char	**get_env_path(void)
{
	int			i;
	char		**cmd_paths;
	extern char	**environ;
	// change ENVIRON to t_env
	i = 0;
	if (environ == NULL)
		return (NULL);
	cmd_paths = NULL;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
		{
			cmd_paths = ft_split((environ[i] + 5), ':');
			if (cmd_paths == NULL)
				return (NULL);
			append_slash(cmd_paths);
			break ;
		}
		i++;
	}
	return (cmd_paths);
}

void	append_slash(char **cmd_paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd_paths[i])
	{
		if (cmd_paths[i][ft_strlen(cmd_paths[i]) - 1] != '/')
		{
			tmp = cmd_paths[i];
			cmd_paths[i] = ft_strjoin(cmd_paths[i], "/");
			free(tmp);
			tmp = NULL;
		}
		i++;
	}
}
