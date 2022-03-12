/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:30 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/13 00:36:34 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	executer(t_table **table)
{
	int		childs;
	int		here_doc;
	t_table	*tmp;
	t_list	*redir_tmp;

	childs = 0;
	tmp = *table;
	here_doc = 0;
	while (tmp)
	{
		if (!check_log_op(tmp->log_op))
			childs++;
		redir_tmp = tmp->redir_in;
		while (redir_tmp)
		{
			if (*(int *)(tmp->redir_in->content) == LESSLESS)
				here_doc++;
			redir_tmp = redir_tmp->next;
		}
		tmp = tmp->next;
	}
	create_child_prcs(table, childs);
}

void	create_child_prcs(t_table **table, int childs)
{
	int		i;
	pid_t	pid;
	t_table	*tmp;
	int		tmp_fd_in;
	int		tmp_fd;
	int		fd[2];

	i = 0;
	tmp_fd_in = STDIN_FILENO;
	tmp = *table;
	while (tmp && i < childs)
	{
		if (tmp->log_op != COMMAND)
			tmp = tmp->next;
		pipe(fd);
		if (!tmp->redir_in)
		{
			tmp_fd = fd[READ];
			fd[READ] = tmp_fd_in;
			tmp_fd_in = tmp_fd;
		}
		else
		{
			tmp_fd = fd[READ];
			fd[READ] = open_file((char *)tmp->infiles->content, O_RDONLY, 0);
			tmp_fd_in = tmp_fd;
		}
		if (i == childs - 1)
			fd[WRITE] = STDOUT_FILENO;
		pid = fork();
		if (pid < 0)
			perror("Could not fork.");
		if (pid == 0)
		{
			child_prc(childs, i, tmp, fd);
		}
		if (fd[READ] != STDIN_FILENO)
			close(fd[READ]);
		if (fd[WRITE] != STDOUT_FILENO)
			close(fd[WRITE]);
		i++;
		tmp = tmp->next;
	}
	while (i != -1)
		i = waitpid(0, NULL, 0);
}

void	child_prc(int childs, int i, t_table *table, int fd[2])
{
	char	**env_arr;

	(void)childs;
	(void)i;
	env_arr = get_env_arr();
	dup2(fd[READ], STDIN_FILENO);
	dup2(fd[WRITE], STDOUT_FILENO);
	if (!built_in_exec(table) && table->cmd_arr[0])
		execve(table->cmd_arr[0], table->cmd_arr, env_arr);
	exit(EXIT_SUCCESS);
}

// // CMD | CMD
// (void) here_doc;
// (void) childs;
// t_table	*tmp1;
// t_table	*tmp2;
// char	**env_arr;
// int fd[2];
// int	tmp_fd;

// tmp1 = *table;
// tmp2 = (*table)->next->next;

// env_arr = get_env_arr();
// pipe(fd);
// int pid = fork();
// if (pid == 0)
// {
// 	close(fd[0]);
// 	tmp_fd = dup2(fd[1], STDOUT_FILENO);
// 	close(fd[1]);
// 	if (!built_in_exec(tmp1))
// 		execve(tmp1->cmd_arr[0], tmp1->cmd_arr, env_arr);
// 	exit(EXIT_SUCCESS) ;
// }
// waitpid(pid, NULL, 0);
// int pid2 = fork();
// if (pid2 == 0)
// {
// 	close(fd[1]);
// 	dup2(fd[0], STDIN_FILENO);
// 	close(fd[0]);
// 	if (!built_in_exec(tmp2))
// 		execve(tmp2->cmd_arr[0], tmp2->cmd_arr, env_arr);
// 	exit(EXIT_SUCCESS);
// }
// close(fd[0]);
// close(fd[1]);
// waitpid(pid2, NULL, 0);
