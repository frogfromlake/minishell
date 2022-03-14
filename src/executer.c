/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:30 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/14 14:42:52 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


static int	child_prc_heredoc(char *delimiter, int *here_fd, int count_cmds);

void	executer(t_table **table)
{
	int		childs;
	t_table	*tmp;

	childs = 0;
	tmp = *table;
	while (tmp)
	{
		if (!check_log_op(tmp->log_op))
			childs++;
		tmp = tmp->next;
	}
	create_child_prcs(table, childs);
}

int	create_child_prcs(t_table **table, int childs)
{
	int		i;
	pid_t	pid;
	t_table	*tmp;
	int		tmp_fd_in;
	int		tmp_fd_out;
	int		tmp_fd;
	int		tmp_fd2;
	int		fd[2];

	i = 0;
	tmp = *table;
	tmp_fd_in = dup(STDIN_FILENO);
	tmp_fd_out = STDOUT_FILENO;
	while (tmp && i < childs)
	{
		pipe(fd);
		if (tmp->log_op != COMMAND)
			tmp = tmp->next;
		if (!tmp->redir_in && !tmp->redir_out) // cmds with pipes
		{
			tmp_fd = fd[READ];
			fd[READ] = tmp_fd_in;
			tmp_fd_in = tmp_fd;
		}
		else if (!tmp->log_op && tmp->redir_in && !tmp->redir_out && !tmp->delimiter) // redir in with pipes
		{
			printf("Infile found\n");
			tmp_fd = fd[READ];
			fd[READ] = open_file((char *)tmp->infiles->content, O_RDONLY, 0);
			if (fd[READ] < 0)
				return (EXIT_FAILURE);
			tmp_fd_in = tmp_fd;
		}
		else if (!tmp->log_op && tmp->redir_out && !tmp->redir_in) // redir out with pipes
		{
			tmp_fd = fd[READ];
			fd[READ] = tmp_fd_in;
			tmp_fd_in = tmp_fd;
			tmp_fd2 = fd[WRITE];
			fd[WRITE] = open_file((char *)tmp->outfiles->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (fd[WRITE] < 0)
				return (EXIT_FAILURE);
			tmp_fd_out = tmp_fd2;
		}
		if (i == childs - 1 && !tmp->redir_out)
			fd[WRITE] = STDOUT_FILENO;
		pid = fork();
		if (pid < 0)
			perror("Could not fork.");
		if (pid == 0)
		{
			child_prc_exec(tmp, fd, childs);
		}
		if (fd[READ] != STDIN_FILENO)
			close(fd[READ]);
		if (fd[WRITE] != STDOUT_FILENO)
			close(fd[WRITE]);
		i++;
		tmp = tmp->next;
	}
	while (waitpid(-1, NULL, 0) != -1)
		continue ;
	return (0);
}

void	child_prc_exec(t_table *table, int fd[2], int childs)
{
	char	**env_arr;
	int		here_fd[2];

	env_arr = get_env_arr();
	if (!table->log_op && table->delimiter) // here_doc
	{
		pipe(here_fd);
		child_prc_heredoc((char *)table->delimiter->content, here_fd, childs);
		dup2(here_fd[READ], STDIN_FILENO);
	}
	else
	{
		dup2(fd[READ], STDIN_FILENO);
		dup2(fd[WRITE], STDOUT_FILENO);
	}
	if (!built_in_exec(table) && table->cmd_arr[0])
		execve(table->cmd_arr[0], table->cmd_arr, env_arr);
	exit(EXIT_SUCCESS);
}

static int	child_prc_heredoc(char *delimiter, int *here_fd, int count_cmds)
{
	int		i;
	char	*read;
	char	*delimiter_nl;

	delimiter_nl = ft_strjoin(delimiter, "\n");
	while (true)
	{
		i = count_cmds;
		while (i)
		{
			write(2, "pipe ", 5);
			i--;
		}
		write(2, "> ", 2);
		read = get_next_line(STDIN_FILENO);
		if (!ft_strcmp(read, delimiter_nl))
			break ;
		write(here_fd[WRITE], read, ft_strlen(read));
		ft_free((void **)&read);
	}
	close(here_fd[WRITE]);
	ft_free((void **)&read);
	ft_free((void **)&delimiter_nl);
	return (EXIT_SUCCESS);
}
