/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:30 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/10 17:47:52 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	executer(t_table **table, t_env **env)
{
	int		childs;
	int		here_doc;
	pid_t	*pids;
	t_table	*tmp;

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
	pids = create_child_prcs(table, env, childs, here_doc);
}

pid_t	*create_child_prcs(t_table **table, t_env **env, int childs, bool here_doc)
{
	int		i;
	t_table	*tmp;
	pid_t	*pid;
	char	**env_arr;
	int		**pipes;

	i = 0;
	pipes = create_pipes_arr(childs - 1);
	pid = malloc(childs * sizeof(pid_t));
	(void)here_doc;
	if (!pid)
		perror("Allocation for PIDS failed.");
	env_arr = get_env_arr(env);
	if (!env_arr)
		perror("Error: ENV is corrupted.");
	tmp = *table;
	while (i < childs && tmp)
	{
		if (tmp->log_op != COMMAND)
		{
			tmp = tmp->next;
			continue ;
		}
		if (check_builtin(tmp))
		{
			builtin_exec(tmp, env, pipes);
			tmp = tmp->next;
			i++;
			continue ;
		}
		pid[i] = fork();
		if (pid[i] < 0)
			perror("Error: couldn't fork.");
		if (pid[i] == 0)
		{
			ft_free((void **)&pid);
			child_prc(childs, i, pipes, tmp, env);
			i++;
			tmp = tmp->next;
		}
		// if (here_doc)
		// 	waitpid(*pid, NULL, 0);
		if (pid[i] != 0)
			waitpid(*pid, NULL, 0);
		i++;
	}
	return (pid);
}

void	child_prc(int childs, int i, int **pipes, t_table *table, t_env **env)
{
	int	ret;
	// int	fd[2];
	(void)env;
	(void)table;
	ret = close_pipes(pipes, childs, i);
	// do stuff
	free_pipes_arr(pipes, childs - 1);
}

int	builtin_exec(t_table *table, t_env **env, int **pipes)
{
	int	fd;
	// printf("%d\n", *pipes[0]);
	(void)pipes;
	if (table->log_op == 0 && table->exe && check_builtin(table))
	{
		if (!ft_strcmp(table->exe, "pwd"))
			ft_pwd();
		if (!ft_strcmp(table->exe, "cd"))
			ft_cd(table, env);
		if (!ft_strcmp(table->exe, "echo"))
			ft_echo(table, fd);
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

int	child_prc_exec(int pipe_read, int pipe_write, t_table *table, t_env **env)
{
	char	**env_arr;

	env_arr = get_env_arr(env);
	dup2(pipe_read, STDIN_FILENO);
	close(pipe_read);
	dup2(pipe_write, STDOUT_FILENO);
	close(pipe_write);
	execve(table->cmd_arr[0], table->cmd_arr, env_arr);
	file_error("minishell", strerror(errno), table->cmd_arr[0]);
	// ft_free_split(cmd);
	return (0);
}










// int	open_file(t_table *table, int mod, int rights)
// {
// 	int	fd;

// 	if (*(int *)(table->redir_in->content))
// 		return (STDIN_FILENO);
// 	fd = open(*(char **)(table->outfiles->content), mod, rights);
// 	if (fd < 0)
// 		file_error("minishell", strerror(errno), table->cmd_arr[0]);
// 	return (fd);
// }

// int	file_error(char *name_b, char *msg, char *name_a)
// {
// 	if (name_b)
// 		ft_putstr_fd(name_b, 2);
// 	if (msg)
// 	{
// 		if (name_b)
// 			ft_putstr_fd(": ", 2);
// 		ft_putstr_fd(msg, 2);
// 	}
// 	if (name_a)
// 	{
// 		if (msg)
// 			ft_putstr_fd(": ", 2);
// 		ft_putstr_fd(name_a, 2);
// 	}
// 	ft_putchar_fd('\n', 2);
// 	return (EXIT_FAILURE);
// }
