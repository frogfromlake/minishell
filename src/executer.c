/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:30 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/10 17:55:45 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	executer(t_table **table, t_env **env)
{
	int		childs;
	int		here_doc;
	t_table	*tmp;
	// pid_t	*pids;

	(void)env;
	childs = 0;
	tmp = *table;
	here_doc = 0;
	while (tmp)
	{
		if (!check_log_op(tmp->log_op))
			childs++;
		while (tmp->redir_in)
		{
			if (*(int *)(tmp->redir_in->content) == LESSLESS)
				here_doc++;
			tmp->redir_in = tmp->redir_in->next;
		}
		tmp = tmp->next;
	}
	// pids = create_child_prcs(table, env, childs, here_doc);
}

int	built_in_exec(t_table *table, t_env **env)
{
	if (table->log_op == 0 && table->exe && check_builtin(table))
	{
		if (!ft_strcmp(table->exe, "pwd"))
			ft_pwd();
		if (!ft_strcmp(table->exe, "cd"))
			ft_cd(table, env);
		if (!ft_strcmp(table->exe, "echo"))
			ft_echo(table, -1);
		if (!ft_strcmp(table->exe, "export"))
			ft_export(env, table);
		if (!ft_strcmp(table->exe, "env"))
			ft_env(env);
		if (!ft_strcmp(table->exe, "exit"))
			ft_exit(table);
		if (!ft_strcmp(table->exe, "unset"))
			ft_unset(env, table);
	}
	return (0);
}
