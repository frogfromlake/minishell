/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:30 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/25 19:33:01 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_loop(t_table *table)
{
	t_table	*tmp;
	t_exec	*fds;

	tmp = table;
	fds = new_exec();
	while (tmp)
	{
		if (tmp->log_op != COMMAND)
			tmp = tmp->next;
		if (tmp->prev == NULL && tmp->next == NULL
			&& !tmp->redir && check_builtin(tmp))
		{
			g_exit_status = built_in_exec(tmp);
			return (g_exit_status);
		}
		else
			fds->pid = create_prcs(tmp, fds);
		fds->i++;
		tmp = tmp->next;
	}
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
	
	return (g_exit_status);
}

int	create_prcs(t_table *table, t_exec *fds)
{
	pipe(fds->fd);
	fds->pid = fork();
	if (fds->pid == 0)
	{
		close(fds->fd[READ]);
		if (!table->prev && !table->next
			&& !table->redir && !check_builtin(table))
			g_exit_status = exec(table);
		else
		{
			route_stdin(table, fds);
			route_stdout(table, fds);
			g_exit_status = exec(table);
		}
	}
	close(fds->tmp_fd);
	close(fds->fd[WRITE]);
	dup2(fds->fd[READ], fds->tmp_fd);
	close(fds->fd[READ]);
	return (fds->pid);
}

void	route_stdin(t_table *table, t_exec *fds)
{
	t_redir	*last_in;
	t_redir	*tmp;

	tmp = table->redir;
	last_in = get_last_in_redir(table->redir);
	while (tmp)
	{
		if (tmp->next && (tmp->type == LESS || tmp->type == LESSLESS || tmp->type == LESSLESS + 1))
		{
			if (tmp->type == LESS)
				fds->file_fd = open_file(tmp->file, O_RDONLY, 0);
			if (tmp->type == LESSLESS)
			{
				pipe(fds->here_fd);
				heredoc(tmp->file, fds, tmp->type);
				dup2(fds->here_fd[WRITE], STDOUT_FILENO);
			}
		}
		if (!tmp->next)
		{
			if (last_in->type == LESS)
			{
				fds->file_fd = open_file(last_in->file, O_RDONLY, 0);
				dup2(fds->file_fd, STDIN_FILENO);
				close(fds->file_fd);
			}
			else if (last_in->type == LESSLESS || last_in->type == LESSLESS + 1)
			{
				pipe(fds->here_fd);
				set_attr_heredoc();
				heredoc(last_in->file, fds, last_in->type);
				unset_attr();
				dup2(fds->here_fd[READ], STDIN_FILENO);
			}
		}
		else
		{
			dup2(fds->tmp_fd, STDIN_FILENO);
			close(fds->tmp_fd);
		}
		tmp = tmp->next;
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
			fds->file_fd =  open_file(last_out->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (fds->file_fd < 0)
				return ;
			dup2(fds->file_fd, STDOUT_FILENO);
			close(fds->file_fd);
		}
		else if (last_out->type == GREATGREAT)
		{
			fds->file_fd = open_file(last_out->file, O_RDWR | O_CREAT | O_APPEND, 0644);
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
		else if (table->next->log_op == AND) // bonus
		{
			dup2(fds->fd[WRITE], fds->stout);
			close(fds->fd[WRITE]);
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

int	exec(t_table *table)
{
	char	**env_arr;

	env_arr = get_env_arr();
	if (!env_arr)
		perror("Could not resolve environ array.\n");
	if (built_in_exec(table))
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(table->cmd_arr[0], table->cmd_arr, env_arr) == -1)
			g_exit_status = -1;
	}
	return (g_exit_status);
}

int	heredoc(char *delimiter, t_exec *fds, int type)
{
	char	*read;
	char	*delimiter_nl;

	delimiter_nl = ft_strjoin(delimiter, "\n");
	while (true)
	{
		while (fds->cmd_count)
		{
			write(2, "> ", 2);
			fds->cmd_count--;
		}
		write(2, "> ", 2);
		read = get_next_line(STDIN_FILENO);
		if (!read || !ft_strcmp(read, delimiter_nl))
		{
			if (!read)
				write(2, "\n", 1);
			break ;
		}
		if (type == 240)
			expand(&read);
		write(fds->here_fd[WRITE], read, ft_strlen(read));
		ft_free((void **)&read);
	}
	// unset_attr();
	// if (fds->here_fd[WRITE] > 0)
	close(fds->here_fd[WRITE]);
	ft_free((void **)&read);
	ft_free((void **)&delimiter_nl);
	return (EXIT_SUCCESS);
}
