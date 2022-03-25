/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:55:12 by fquist            #+#    #+#             */
/*   Updated: 2022/03/25 16:56:25 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	sigint_handler(int sig);
void	sigint_handler_heredoc(int sig);
void	ft_sigchild(int sig);
void	ft_sigchild1(int sig);
void	set_attr(void);
void	set_attr_heredoc(void);
void	unset_attr(void);

#endif