/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:00:44 by fquist            #+#    #+#             */
/*   Updated: 2022/03/26 13:39:12 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

void	exec_loop(t_table *table);
int		create_prcs(t_table *table, t_exec *fds);
void	route_stdin(t_table *table, t_exec *fds);
void	route_stdout(t_table *table, t_exec *fds);
int		exec(t_table *table);
int		heredoc(char *delimiter, t_exec *fds, int type);

int		open_file(char *file, int mod, int rights);
int		file_error(char *name_b, char *msg, char *name_a);

int		operation_logic(t_table *table, t_exec *fds);

#endif