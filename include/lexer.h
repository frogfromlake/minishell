/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:15:14 by fquist            #+#    #+#             */
/*   Updated: 2022/03/25 16:19:17 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

int		lexer(t_node **head, char *input);

char	*get_word(char **input);
char	*get_word_ws(char **input); // TODO: delete this declaration!!

bool	check_whitespace(char c);
bool	check_metachar(char c);
bool	check_quotes(char c);
bool	check_redir(t_type type);
bool	check_log_op(t_type c);

#endif