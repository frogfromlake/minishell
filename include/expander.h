/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:21:31 by fquist            #+#    #+#             */
/*   Updated: 2022/03/25 16:25:55 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

void	expand(char **str);
int		expander(t_node **head);

void	dollar_expand(t_stringbuilder **sb, char **tmp);
void	dquote_expand(t_stringbuilder **sb, char **tmp);
void	squote_no_expand(t_stringbuilder **sb, char **tmp);

#endif