/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelix <nelix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 16:40:19 by fquist            #+#    #+#             */
/*   Updated: 2022/03/03 06:36:17 by nelix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	child_prc_heredoc(char *delimiter, int pipe_write, int count_cmds);

pid_t	*create_child_prcs(int childs, t_table **table, bool here_doc)
{
	int		i;
	int		**pipes;
	pid_t	*pid;

	i = 0;
	pipes = create_pipes_arr(childs - 1);
	pid = malloc(childs * sizeof(pid_t));
	if (pid == NULL)
		exit(ENOMEM);
	while (i < childs)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			ft_free((void **)&pid);
			child_prc(childs, i, pipes, table);
		}
		if (here_doc)
			waitpid(pid[0], NULL, 0);
		i++;
	}
	close_pipes(pipes, childs, -1);
	free_pipes_arr(pipes, childs - 1);
	return (pid);
}

void	child_prc(int childs, int i, int **pipes, t_table **table)
{
	int	ret;
	int	fd[2];

	ret = close_pipes(pipes, childs, i);
	if (i > 0)
		fd[0] = pipes[i - 1][0];
	if (i != childs - 1)
		fd[1] = pipes[i][1];
	if (i == 0)
		fd[0] = open_file((*table)->redir_in, O_RDONLY, 0); // switched argv[1] with (*table)->redir_in
else if (i == childs - 1 && ft_strncmp((*table)->redir_in, "<<", 3) == 0) // switched argv[1] with (*table)->redir_in
	fd[1] = open_file((*table)->next->next->exe, O_RDWR | O_CREAT | O_APPEND, 0644); // switched argv[childs + 2] with (*table)->next->next->exe
	else if (i == childs - 1)
		fd[1] = open_file((*table)->next->next->exe, O_RDWR | O_CREAT | O_TRUNC, 0644); // switched argv[childs + 2] with (*table)->next->next->exe
	if (fd[0] == 0 && fd[1] > 0)
		ret = child_prc_heredoc((*table)->next->exe, fd[1], childs - 1); // switched argv[2] with (*table)->next->exe
	else if (fd[0] > 0 && fd[1] > 0)
		ret = child_prc_exec(fd[0], fd[1], (*table)->next->next->exe); // switched argv[i + 2] with (*table)->next->exe
	else if (ret == EXIT_SUCCESS)
		ret = EXIT_FAILURE;
	free_pipes_arr(pipes, childs - 1);
	exit(ret);
}

static int	child_prc_heredoc(char *delimiter, int pipe_write, int count_cmds)
{
	int		i;
	char	*read;
	char	*delimiter_nl;

	delimiter_nl = ft_strjoin(delimiter, "\n");
	while (true)
	{
		i = count_cmds - 1;
		while (i)
		{
			write(2, "> ", 3);
			i--;
		}
		write(2, "> ", 3);
		read = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(read, delimiter_nl, ft_strlen(delimiter) + 1))
			break ;
		write(pipe_write, read, ft_strlen(read));
		ft_free((void **)&read);
	}
	close(pipe_write);
	ft_free((void **)&read);
	ft_free((void **)&delimiter_nl);
	return (EXIT_SUCCESS);
}

int	child_prc_exec(int pipe_read, int pipe_write, t_table *str_cmd)
{
	int			code;
	char		**cmd;
	// extern char	**environ;
	t_env		**env;

	cmd = get_commands(str_cmd, &code);
	if (cmd == NULL)
		return (code);
	dup2(pipe_read, STDIN_FILENO);
	close(pipe_read);
	dup2(pipe_write, STDOUT_FILENO);
	close(pipe_write);
	execve(cmd[0], cmd, env);
	file_error("minishell", strerror(errno), cmd[0]);
	ft_free_split(cmd);
	return (EXIT_FAILURE);
}
