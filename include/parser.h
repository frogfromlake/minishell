/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:27:18 by fquist            #+#    #+#             */
/*   Updated: 2022/03/27 21:08:46 by dmontema         ###   ########.fr       */
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
int		redir_parser(t_token *curr_t, t_table **new);
void	trim_quotes(t_token **token);
int		error_msg(char *error_msg, int r_value);

#endif