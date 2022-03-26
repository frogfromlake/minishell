/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:44:58 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/26 03:08:34 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_heredoc(t_redir *redir)
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

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigint_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		change_termios(false);
		g_exit_status = FAIL;
		exit(g_exit_status);
	}
}

void	sigchild_handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	if (sig == SIGQUIT)
		write(1, "Quit: 3\n", 9);
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
