/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:30 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/15 02:56:25 by fquist           ###   ########.fr       */
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

	i = 0;
	save = 0;
	pid = 0;
	exit_status = 0;
	tmp = table;
	while (tmp)
	{
		if (tmp->next == NULL && !tmp->redir && built_in_exec(tmp))
			return (1);
		else
			pid = create_prcs(tmp, pid);
		tmp = tmp->next;
	}
	while(i != -1)
	{
		i = waitpid(0, &save, 0);
		if (i == pid)
			exit_status = save;
			return (WEXITSTATUS(exit_status));
	}
	return (0);
}

int	create_prcs(t_table *table, int pid)
{
	int	fd[2];
	int	tmp_fd;

	tmp_fd = dup(STDIN_FILENO);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (table->prev == NULL && table->next == NULL && !table->redir)
			exec(table);
		route_stdin(table, fd[READ], tmp_fd);
		route_stdout(table, fd[WRITE]);
		if (check_builtin(table))
			built_in_exec(table);
		// else if (table->redir->type == LESSLESS)
		// 	heredoc(table->redir->file, here_fd);
		else
		{
			printf("JETZT GEHTS LOS !!11!\n");
			exec(table);
		}
	}
	// sig(SIGQUIT);
	// sig(SIINT);
	close(tmp_fd);
	close(fd[WRITE]);
	dup2(fd[READ], tmp_fd);
	close(fd[READ]);
	return (0);
}

void	route_stdin(t_table *table, int fd_read, int tmp_fd)
{
	int		file_fd;
	t_redir	*last_in;
	
	last_in = get_last_in_redir(table->redir);
	if (last_in->type == LESS)
	{
		file_fd = open_file(last_in->file, O_RDONLY, 0); // last file?
		close(fd_read);
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);
	}
	else if ((table->log_op == PIPE) || (last_in->type == LESSLESS))
	{
		close(fd_read);
		dup2(tmp_fd, STDIN_FILENO);
		// close?
		close(tmp_fd);
		// get file fd from open?
		file_fd = dup(tmp_fd);
		if (last_in->type == LESSLESS)
			heredoc(table, table->redir->file, file_fd);
	}
	printf("JETZT GEHTS LOS !!11!\n");
}

void	route_stdout(t_table *table, int fd_write)
{
	t_redir	*last_out;
	int		file_fd;

	last_out = get_last_out_redir(table->redir);
	if ((last_out->type == GREAT) || last_out->type == GREATGREAT)
	{
		file_fd = open_file(last_out->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		dup2(file_fd, STDOUT_FILENO);
		close(file_fd);
		close(fd_write);
	}
	else if (table->next == NULL)
		close(fd_write);
	else
	{
		dup2(fd_write, STDOUT_FILENO);
		file_fd = open_file(last_out->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		file_fd = dup(fd_write);
		close(fd_write);
	}
}

int	heredoc(t_table *table, char *delimiter, int fd)
{
	int		count_cmds;
	char	*read;
	char	*delimiter_nl;
	t_table	*tmp;

	count_cmds = 0;
	delimiter_nl = ft_strjoin(delimiter, "\n");
	tmp = table;
	while (table)
	{
		count_cmds++;
		tmp = tmp->next;
	}
	while (true)
	{
		while (count_cmds)
		{
			write(2, "> ", 2);
			count_cmds--;
		}
		write(2, "> ", 2);
		read = get_next_line(STDIN_FILENO);
		if (!ft_strcmp(read, delimiter_nl))
			break ;
		write(fd, read, ft_strlen(read));
		ft_free((void **)&read);
	}
	// close(here_fd[WRITE]);
	ft_free((void **)&read);
	ft_free((void **)&delimiter_nl);
	return (EXIT_SUCCESS);
}

void	exec(t_table *table)
{
	char	**env_arr;

	env_arr = get_env_arr();
	if (!env_arr)
		perror("Could not resolve environ array.\n");
	execve(table->cmd_arr[0], table->cmd_arr, env_arr);
	// free_list()
	exit(EXIT_FAILURE);
}





























// int	create_child_prcs(t_table **table, int childs)
// {
// 	int		i;
// 	pid_t	pid;
// 	t_table	*tmp;	
// 	int		tmp_fd;
// 	int		fd[2];

// 	i = 0;
// 	tmp = *table;
// 	tmp_fd = dup(STDIN_FILENO);
// 	while (tmp && i < childs)
// 	{
// 		if (tmp->log_op != COMMAND)
// 			tmp = tmp->next;
// 		if ((!tmp->prev && !tmp->next) || (i == childs -1 && !tmp->redir_out))
// 		{
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				dup2(tmp_fd, STDIN_FILENO);
// 				if (child_prc_exec(&tmp, tmp_fd, childs))
// 					return (1);
// 			}
// 			else
// 			{
// 				close(tmp_fd);
// 				while (waitpid(-1, NULL, WUNTRACED) != -1)
// 					return (0);
// 				tmp_fd = dup(STDIN_FILENO);
// 			}
// 		}
// 		if (!tmp->redir_in && !tmp->redir_out) // cmds with pipes
// 		{
// 			pipe(fd);
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				dup2(tmp_fd, STDIN_FILENO);
// 				dup2(fd[WRITE], STDOUT_FILENO);
// 				close(fd[READ]);
// 				close(fd[WRITE]);
// 				if (child_prc_exec(&tmp, tmp_fd, childs))
// 					return (1);
// 			}
// 			else
// 			{
// 				close(fd[WRITE]);
// 				close(tmp_fd);
// 				tmp_fd = dup(fd[READ]);
// 				close(fd[READ]);
// 			}
// 		}
// 		// else if (!tmp->log_op && tmp->redir_in && !tmp->redir_out && !tmp->delimiter) // redir in with pipes
// 		// {
			
// 		// }
// 		// else if (!tmp->log_op && tmp->redir_out && !tmp->redir_in) // redir out with pipes
// 		// {
			
// 		// }
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	close(tmp_fd);
// 	while (waitpid(-1, NULL, WUNTRACED) != -1)
// 		return (0);
// 	return (0);
// }


// int	create_child_prcs(t_table **table, int childs)
// {
// 	int		i;
// 	pid_t	pid;
// 	t_table	*tmp;
// 	int		tmp_fd_in;
// 	int		tmp_fd_out;
// 	int		tmp_fd;
// 	int		tmp_fd2;
// 	int		fd[2];

// 	(void) tmp_fd_out;
// 	i = 0;
// 	tmp = *table;
// 	tmp_fd_in = dup(STDIN_FILENO);
// 	tmp_fd_out = STDOUT_FILENO;
// 	while (tmp && i < childs)
// 	{
// 		pipe(fd);
// 		if (tmp->log_op != COMMAND)
// 			tmp = tmp->next;
// 		if (!tmp->redir_in && !tmp->redir_out) // cmds with pipes
// 		{
// 			tmp_fd = fd[READ];
// 			fd[READ] = tmp_fd_in;
// 			tmp_fd_in = tmp_fd;
// 		}
// 		else if (!tmp->log_op && tmp->redir_in && !tmp->redir_out && !tmp->delimiter) // redir in with pipes
// 		{
// 			printf("Infile found\n");
// 			tmp_fd = fd[READ];
// 			fd[READ] = open_file((char *)tmp->infiles->content, O_RDONLY, 0);
// 			if (fd[READ] < 0)
// 				return (EXIT_FAILURE);
// 			tmp_fd_in = tmp_fd;
// 		}
// 		else if (!tmp->log_op && tmp->redir_out && !tmp->redir_in) // redir out with pipes
// 		{
// 			tmp_fd = fd[READ];
// 			fd[READ] = tmp_fd_in;
// 			tmp_fd_in = tmp_fd;
// 			tmp_fd2 = fd[WRITE];
// 			fd[WRITE] = open_file((char *)tmp->outfiles->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 			if (fd[WRITE] < 0)
// 				return (EXIT_FAILURE);
// 			tmp_fd_out = tmp_fd2;
// 		}
// 		if (i == childs - 1 && !tmp->redir_out)
// 			fd[WRITE] = STDOUT_FILENO;
// 		pid = fork();
// 		if (pid < 0)
// 			perror("Could not fork.");
// 		if (pid == 0)
// 		{
// 			child_prc_exec(tmp, fd, childs);
// 		}
// 		if (fd[READ] != STDIN_FILENO)
// 			close(fd[READ]);
// 		if (fd[WRITE] != STDOUT_FILENO)
// 			close(fd[WRITE]);
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	while (waitpid(-1, NULL, 0) != -1)
// 		continue ;
// 	return (0);
// }

// void	child_prc_exec(t_table *table, int fd[2], int childs)
// {
// 	char	**env_arr;
// 	int		here_fd[2];

// 	env_arr = get_env_arr();
// 	if (!table->log_op && table->delimiter) // here_doc
// 	{
// 		pipe(here_fd);
// 		child_prc_heredoc((char *)table->delimiter->content, here_fd, childs);
// 		dup2(here_fd[READ], STDIN_FILENO);
// 	}
// 	else
// 	{
// 		dup2(fd[READ], STDIN_FILENO);
// 		dup2(fd[WRITE], STDOUT_FILENO);
// 	}
// 	if (!built_in_exec(table) && table->cmd_arr[0])
// 		execve(table->cmd_arr[0], table->cmd_arr, env_arr);
// 	exit(EXIT_SUCCESS);
// }

// static int	child_prc_heredoc(char *delimiter, int *here_fd, int count_cmds)
// {
// 	int		i;
// 	char	*read;
// 	char	*delimiter_nl;

// 	delimiter_nl = ft_strjoin(delimiter, "\n");
// 	while (true)
// 	{
// 		i = count_cmds;
// 		while (i)
// 		{
// 			write(2, "> ", 2);
// 			i--;
// 		}
// 		write(2, "> ", 2);
// 		read = get_next_line(STDIN_FILENO);
// 		if (!ft_strcmp(read, delimiter_nl))
// 			break ;
// 		write(here_fd[WRITE], read, ft_strlen(read));
// 		ft_free((void **)&read);
// 	}
// 	close(here_fd[WRITE]);
// 	ft_free((void **)&read);
// 	ft_free((void **)&delimiter_nl);
// 	return (EXIT_SUCCESS);
// }
