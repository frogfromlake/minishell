/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:15:14 by fquist            #+#    #+#             */
/*   Updated: 2022/03/28 22:57:46 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

int		lexer(t_node **head, char *input);

char	*get_word(char **input);
char	*get_redir_char(char **input);

bool	check_whitespace(char c);
bool	check_metachar(char c);
bool	check_quotes(char c);
bool	check_redir(t_type type);
bool	check_log_op(t_type c);

#endif