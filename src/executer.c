/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:30 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/08 18:15:07 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	executer(t_table **table, t_env **env)
{
	int		childs;
	int		pipes;
	t_table	*tmp;

	childs = 0;
	tmp = *table;
	(void)env;
	while (tmp)
	{
		if (!check_log_op(tmp->log_op))
			childs++;
		tmp = tmp->next;
	}
	pipes = childs - 1;
	create_child_prcs(table, childs, pipes, env);
	// execve((*table)->cmd_arr[0], (*table)->cmd_arr, &(*env)->var);
}

int	*create_child_prcs(t_table **table, int childs, int pipes, t_env **env)
{
	int		i;
	pid_t	*pids;
	char	**env_arr;

	i = 0;
	(void)pipes;
	pids = malloc(childs * sizeof(pid_t));
	env_arr = get_env_arr(env);
	while (i < childs)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			perror("Error: couldn't fork.");
		if (pids[i] == 0)
		{
			ft_free((void **)&pids);
			execve((*table)->cmd_arr[0], (*table)->cmd_arr, env_arr);
		}
		if (pids[i] != 0)
			waitpid(*pids, NULL, 0);
		i++;
	}
	ft_free_array(env_arr, false, false);
	return (pids);
}
