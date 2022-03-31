/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:30 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/31 18:55:10 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	create_prcs(t_table *table, t_exec *fds);
static void	end_prcs(t_exec *fds);

static bool	check_single_built_in(t_table *tmp)
{
	if (tmp->prev == NULL && tmp->next == NULL
		&& !tmp->redir && check_builtin(tmp))
	{
		g_exit_status = built_in_exec(tmp);
		return (true);
	}
	return (false);
}

void	exec_loop(t_table *table)
{
	t_table	*tmp;
	t_exec	*fds;

	tmp = table;
	fds = new_exec();
	while (tmp)
	{
		if (tmp->log_op != COMMAND)
		{
			tmp = tmp->next;
			continue ;
		}
		if (check_single_built_in(tmp))
			break ;
		else
		{
			fds->i++;
			if (create_prcs(tmp, fds) < 0)
				end_prcs(fds);
		}
		tmp = tmp->next;
	}
	end_prcs(fds);
}

static int	create_prcs(t_table *table, t_exec *fds)
{
	pipe(fds->fd);
	define_sig_prc(table);
	fds->pid = fork();
	if (fds->pid == 0)
	{
		close(fds->fd[READ]);
		if (!table->prev && !table->next
			&& !table->redir && !check_builtin(table))
			g_exit_status = exec(table);
		else
		{
			if (route_stdin(table, fds) < 0)
				return (-1);
			if (route_stdout(table, fds) < 0)
				return (-1);
			g_exit_status = exec(table);
		}
	}
	close(fds->tmp_fd);
	dup2(fds->fd[READ], fds->tmp_fd);
	close(fds->fd[READ]);
	close(fds->fd[WRITE]);
	return (fds->pid);
}

static void	end_prcs(t_exec *fds)
{
	close(fds->stin);
	close(fds->stout);
	close(fds->tmp_fd);
	while (fds->i > 0)
	{
		waitpid(0, &fds->pid, 0);
		if (WIFEXITED(fds->pid))
			g_exit_status = WEXITSTATUS(fds->pid);
		fds->i--;
	}
	free(fds);
}

int	exec(t_table *table)
{
	char	**env_arr;

	env_arr = get_env_arr();
	if (!env_arr)
		perror("Could not resolve environ array.\n");
	if (check_builtin(table))
	{
		built_in_exec(table);
		ft_free_split(env_arr);
	}
	else if (table->exe)
	{
		execve(table->cmd_arr[0], table->cmd_arr, env_arr);
		g_exit_status = -1;
		ft_free_split(env_arr);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
