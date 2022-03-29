/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 04:10:34 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/29 21:17:44 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_builtin(t_table *table)
{
	if (!table->exe)
		return (false);
	if (!ft_strcmp_upper_lower(table->exe, "pwd")
		|| !ft_strcmp(table->exe, "cd")
		|| !ft_strcmp_upper_lower(table->exe, "echo")
		|| !ft_strcmp(table->exe, "export")
		|| !ft_strcmp_upper_lower(table->exe, "env")
		|| !ft_strcmp(table->exe, "exit")
		|| !ft_strcmp(table->exe, "unset"))
		return (true);
	return (false);
}

int	built_in_exec(t_table *table)
{
	if (table->log_op == 0 && table->exe)
	{
		if (!ft_strcmp_upper_lower(table->exe, "pwd"))
			ft_pwd();
		if (!ft_strcmp(table->exe, "cd"))
			ft_cd(table);
		if (!ft_strcmp_upper_lower(table->exe, "echo"))
			ft_echo(table);
		if (!ft_strcmp(table->exe, "export"))
			ft_export(table);
		if (!ft_strcmp_upper_lower(table->exe, "env"))
			ft_env();
		if (!ft_strcmp(table->exe, "exit"))
			ft_exit(table);
		if (!ft_strcmp(table->exe, "unset"))
			ft_unset(table);
		return (g_exit_status);
	}
	return (FAIL);
}
