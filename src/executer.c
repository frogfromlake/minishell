/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:30 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/11 00:51:08 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	executer(t_table **table)
{
	int		childs;
	int		here_doc;
	// t_table	*tmp;
	// pid_t	*pids;

	childs = 0;
	// tmp = *table;
	here_doc = 0;
	// while (tmp)
	// {
	// 	if (!check_log_op(tmp->log_op))
	// 		childs++;
		// while (tmp->redir_in)
		// {
		// 	if (*(int *)(tmp->redir_in->content) == LESSLESS)
		// 		here_doc++;
		// 	tmp->redir_in = tmp->redir_in->next;
		// }
	// 	tmp = tmp->next;
	// }
	create_child_prcs(table, childs, here_doc);
}

void	create_child_prcs(t_table **table, int childs, bool here_doc) // CMD | CMD
{
	(void) here_doc;
	(void) childs;
	t_table	*tmp1;
	t_table	*tmp2;
	char	**env_arr;
	
	env_arr = get_env_arr();
	tmp1 = *table;
	tmp2 = (*table)->next->next;
	int fd[2];

	pipe(fd);
	int pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_echo(tmp1, 1);
		exit(EXIT_SUCCESS) ;
	}
	waitpid(pid, NULL, 0);
	int pid2 = fork();
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		execve(tmp2->cmd_arr[0], tmp2->cmd_arr, env_arr);
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid2, NULL, 0);
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
			ft_echo(table, -1);
		if (!ft_strcmp(table->exe, "export"))
			ft_export(table);
		if (!ft_strcmp(table->exe, "env"))
			ft_env();
		if (!ft_strcmp(table->exe, "exit"))
			ft_exit(table);
		if (!ft_strcmp(table->exe, "unset"))
			ft_unset(table);
	}
	return (0);
}
