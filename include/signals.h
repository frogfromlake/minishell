/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:55:12 by fquist            #+#    #+#             */
/*   Updated: 2022/03/26 03:09:54 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	sigint_handler(int sig);
void	sigint_handler_heredoc(int sig);
void	sigchild_handler(int sig);
int		change_termios(bool toggle);
void	define_sig_prc(t_table *table);
bool	check_heredoc(t_redir *redir);

#endif