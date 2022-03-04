/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:30 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/04 03:19:15 by dmontema         ###   ########.fr       */
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
	while (tmp)
	{
		if (!check_log_op(tmp->log_op))
			childs++;
		tmp = tmp->next;
	}
	pipes = childs - 1;
	execve((*table)->cmd_arr[0], (*table)->cmd_arr, &(*env)->var);
}
