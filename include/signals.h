/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:55:12 by fquist            #+#    #+#             */
/*   Updated: 2022/03/30 23:39:28 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	handle_interactive(void);
void	define_sig_prc(t_table *table);
int		change_termios(bool toggle);
void	sigint_handler(int sig);
void	sigint_handler_heredoc(int sig);
void	sigchild_handler(int sig);

#endif