/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:28:45 by fquist            #+#    #+#             */
/*   Updated: 2022/03/31 22:19:45 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	here_doc_print(t_exec *fds)
{
	while (fds->cmd_count)
	{
		write(2, "> ", 2);
		fds->cmd_count--;
	}
	write(2, "> ", 2);
}

int	heredoc(char *delimiter, t_exec *fds, int type)
{
	char	*read;
	char	*delimiter_nl;

	delimiter_nl = ft_strjoin(delimiter, "\n");
	signal(SIGINT, sigint_handler_heredoc);
	while (true)
	{
		here_doc_print(fds);
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
	change_termios(false);
	close(fds->here_fd[WRITE]);
	ft_free((void **)&read);
	ft_free((void **)&delimiter_nl);
	return (EXIT_SUCCESS);
}
