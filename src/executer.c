/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:30 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/15 23:47:18 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_loop(t_table *table)
{
	int		i;
	int		save;
	int		pid;
	int		exit_status;
	t_table *tmp;
	t_exec	*fds;

	i = 0;
	save = 0;
	pid = 0;
	exit_status = 0;
	tmp = table;
	fds = new_exec();
	while (tmp)
	{
		if (tmp->log_op != COMMAND)
			tmp = tmp->next;
		if (tmp->prev == NULL && tmp->next == NULL && !tmp->redir && built_in_exec(tmp))
			return (1);
		else
			pid = create_prcs(tmp, fds, pid);
		i++;
		tmp = tmp->next;
	}
	close(fds->stin);
	close(fds->stout);
	close(fds->tmp_fd);
	while (i > 0)
	{
		waitpid(0, &pid, 0);
		if (WIFEXITED(pid))
			exit_status = WEXITSTATUS(pid);
		i--;
	}
	return (0);
}

int	create_prcs(t_table *table, t_exec *fds, int pid)
{
	pipe(fds->fd);
	pid = fork();
	if (pid == 0)
	{
		close(fds->fd[READ]);
		if (!table->prev && !table->next && !table->redir && !check_builtin(table))
			exec(table);
		else
		{
			route_stdin(table, fds);
			route_stdout(table, fds);
			// built_ins
				exec(table);
			exit(EXIT_FAILURE);
		}
	}
	close(fds->tmp_fd);
	close(fds->fd[WRITE]);
	dup2(fds->fd[READ], fds->tmp_fd);
	close(fds->fd[READ]);
	return (pid);
}

void	route_stdin(t_table *table, t_exec *fds)
{
	t_redir	*last_in;
	
	last_in = get_last_in_redir(table->redir);
	if (last_in)
	{
		if (last_in->type == LESS)
		{
			fds->file_fd = open_file(fds, last_in->file, O_RDONLY, 0);
			dup2(fds->file_fd, STDIN_FILENO);
			close(fds->file_fd);
		}
		else if (last_in->type == LESSLESS)
		{
			pipe(fds->here_fd);
			heredoc(table, last_in->file, fds);
			dup2(fds->here_fd[READ], STDIN_FILENO);
		}
	}
	else
	{
		dup2(fds->tmp_fd, STDIN_FILENO);
		close(fds->tmp_fd);
	}
}

void	route_stdout(t_table *table, t_exec *fds)
{
	t_redir	*last_out;

	last_out = get_last_out_redir(table->redir);
	if (last_out)
	{
		if (last_out->type == GREAT)
		{
			fds->file_fd = open_file(fds, last_out->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (fds->file_fd < 0)
				return ;
			dup2(fds->file_fd, STDOUT_FILENO);
			close(fds->file_fd);
		}
		else if (last_out->type == GREATGREAT)
		{
			fds->file_fd = open_file(fds, last_out->file, O_RDWR | O_CREAT | O_APPEND, 0644);
			dup2(fds->file_fd, STDOUT_FILENO);
			close(fds->file_fd);
		}
	}
	else 
		{
			if (table->next == NULL)
			{
				if (fds->here_fd[READ] > 0 || fds->here_fd[WRITE] > 0)
				{
					dup2(fds->stout, fds->here_fd[WRITE]);
					close(fds->stout);
				}
				dup2(fds->stout, STDOUT_FILENO);
				close(fds->stout);
			}
			else
			{
				if (fds->here_fd[READ] > 0 || fds->here_fd[WRITE] > 0)
				{
					dup2(fds->fd[READ], fds->here_fd[WRITE]);
					close(fds->fd[READ]);
				}
				dup2(fds->fd[WRITE], STDOUT_FILENO);
				close(fds->fd[WRITE]);
			}
		}
}

void	exec(t_table *table)
{
	char	**env_arr;

	env_arr = get_env_arr();
	if (!env_arr)
		perror("Could not resolve environ array.\n");
	if (!built_in_exec(table))
	{
		execve(table->cmd_arr[0], table->cmd_arr, env_arr);
		perror("execve failed\n");
	}
	exit(EXIT_FAILURE);
}


int	heredoc(t_table *table, char *delimiter, t_exec *fds)
{
	char	*read;
	char	*delimiter_nl;
	t_table	*tmp;

	delimiter_nl = ft_strjoin(delimiter, "\n");
	tmp = table;
	while (true)
	{
		while (fds->cmd_count)
		{
			write(2, "> ", 2);
			fds->cmd_count--;
		}
		write(2, "> ", 2);
		read = get_next_line(STDIN_FILENO);
		if (!ft_strcmp(read, delimiter_nl))
			break ;
		write(fds->here_fd[WRITE], read, ft_strlen(read));
		ft_free((void **)&read);
	}
	ft_free((void **)&read);
	ft_free((void **)&delimiter_nl);
	return (EXIT_SUCCESS);
}
