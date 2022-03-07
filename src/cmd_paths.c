/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:50:10 by fquist            #+#    #+#             */
/*   Updated: 2022/03/07 19:54:40 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_cmd_path(t_table **table, t_env **env)
{
	int		i;
	char	*tmp;
	char	**cmd_paths;

	i = 0;
	if (access((*table)->exe, F_OK) == 0)
		return (0);
	cmd_paths = get_env_path(env);
	if (cmd_paths == NULL)
		return (ENOMEM);
	while (cmd_paths[i])
	{
		tmp = ft_strjoin(cmd_paths[i], (*table)->exe);
		if (access(tmp, F_OK) == 0)
		{
			free((*table)->cmd_arr[0]);
			(*table)->cmd_arr[0] = ft_strdup(tmp);
			free(tmp);
			ft_free_split(cmd_paths);
			return (0);
		}
		free(tmp);
		i++;
	}
	ft_free_split(cmd_paths);
	return (127);
}

char	**get_env_path(t_env **env)
{
	char		**cmd_paths;
	t_env		*tmp;

	tmp = *env;
	if (env == NULL)
		return (NULL);
	cmd_paths = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PATH=", 5) == 0)
		{
			cmd_paths = ft_split((tmp->var + 5), ':'); // ????? -> skips "PATH="
			if (cmd_paths == NULL)
				return (NULL);
			append_slash(cmd_paths);
			break ;
		}
		tmp = tmp->next;
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
