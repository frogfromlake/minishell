/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 04:10:34 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/20 04:10:34 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_builtin(t_table *table)
{
	if (!ft_strcmp(table->exe, "pwd")
		|| !ft_strcmp(table->exe, "cd")
		|| !ft_strcmp(table->exe, "echo")
		|| !ft_strcmp(table->exe, "export")
		|| !ft_strcmp(table->exe, "env")
		|| !ft_strcmp(table->exe, "exit")
		|| !ft_strcmp(table->exe, "unset"))
		return (true);
	return (false);
}

int	built_in_exec(t_table *table)
{
	if (table->log_op == 0 && table->exe && check_builtin(table))
	{
		if (!ft_strcmp(table->exe, "pwd"))
			ft_pwd();
		if (!ft_strcmp(table->exe, "cd"))
			ft_cd(table);
		if (!ft_strcmp(table->exe, "echo"))
			ft_echo(table);
		if (!ft_strcmp(table->exe, "export"))
			ft_export(table->args);
		if (!ft_strcmp(table->exe, "env"))
			ft_env();
		if (!ft_strcmp(table->exe, "exit"))
			ft_exit(table);
		if (!ft_strcmp(table->exe, "unset"))
			ft_unset(table);
		return (1);
	}
	return (0);
}