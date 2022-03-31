/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:44:58 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/30 23:53:08 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	check_heredoc(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == LESSLESS || redir->type == LESSLESS + 1)
			return (true);
		redir = redir->next;
	}
	return (false);
}

void	define_sig_prc(t_table *table)
{
	if (check_heredoc(table->redir))
	{
		change_termios(true);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, sigchild_handler);
		signal(SIGQUIT, sigchild_handler);
	}
}

int	change_termios(bool hide)
{
	struct termios	term;

	if (tcgetattr(STDOUT_FILENO, &term) == -1)
		return (1);
	if (hide)
		term.c_lflag &= ~(ECHOCTL);
	else
		term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDOUT_FILENO, TCSANOW, &term) == -1)
		return (1);
	return (0);
}

void	handle_interactive(void)
{
	change_termios(true);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}
