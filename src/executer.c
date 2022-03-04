/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:30 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/04 17:38:07 by dmontema         ###   ########.fr       */
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

	i = 0;
	(void)pipes;
	pids = malloc(childs * sizeof(pid_t));
	if (pids)
	printf("childs: %d\n", childs);
	while (i < childs)
	{
		pids[i] = fork();
		printf("pid: %d\n", pids[i]);
		if (pids[i] < 0)
			perror("Error: couldn't fork.");
		if (pids[i] == 0)
		{
 			ft_free((void **)&pids);
			execve((*table)->cmd_arr[0], (*table)->cmd_arr, &(*env)->var);
		}
		if (pids[i] != 0)
			waitpid(*pids, NULL, 0);
		i++;
	}
	return (pids);
}
