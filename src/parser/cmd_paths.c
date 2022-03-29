/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:50:10 by fquist            #+#    #+#             */
/*   Updated: 2022/03/12 21:09:18 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	join_cmd_path(t_table **new, char **cmd_paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd_paths[i])
	{
		tmp = ft_strjoin(cmd_paths[i], (*new)->exe);
		if (access(tmp, F_OK) == 0)
		{
			free((*new)->cmd_arr[0]);
			(*new)->cmd_arr[0] = ft_strdup(tmp);
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

static void	append_slash(char **cmd_paths)
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

static char	**get_env_path(t_env *env)
{
	char		**cmd_paths;

	if (env == NULL)
		return (NULL);
	cmd_paths = NULL;
	while (env)
	{
		if (ft_strncmp(env->var, "PATH=", 5) == 0)
		{
			cmd_paths = ft_split((env->var + 5), ':');
			if (cmd_paths == NULL)
				return (NULL);
			append_slash(cmd_paths);
			break ;
		}
		env = env->next;
	}
	return (cmd_paths);
}

int	set_cmd_path(t_table **new)
{
	int		exit;
	char	**cmd_paths;
	t_env	*env;

	if (access((*new)->exe, F_OK) == 0)
	{
		(*new)->cmd_arr[0] = ft_strdup((*new)->exe);
		return (0);
	}
	env = *get_env(NULL);
	cmd_paths = get_env_path(env);
	if (cmd_paths == NULL)
		return (ENOMEM);
	exit = join_cmd_path(new, cmd_paths);
	return (exit);
}
