/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:27:18 by fquist            #+#    #+#             */
/*   Updated: 2022/03/27 00:01:11 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int		parser(t_node **node, t_table **table);
void	add_args_to_arr(t_token *token, t_table **new);
int		set_cmd_path(t_table **table, t_env **env);
char	**get_env_path(t_env **env);
void	append_slash(char **cmd_paths);
int		command_parser(t_token *token, t_table **new);
int		define_echo_args(t_token *token, t_table **new);
int		valid_name(t_token **token);
void	create_cmd_table(t_node **node, t_table **table);
int		redir_parser(t_token *curr_t, t_table **new);
void	trim_quotes(t_token **token);
int		error_msg(char *error_msg, int r_value);

#endif