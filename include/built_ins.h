/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:25:51 by fquist            #+#    #+#             */
/*   Updated: 2022/03/25 16:07:25 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

/***	Built_in exec	***/
int		built_in_exec(t_table *table);
bool	check_builtin(t_table *table);

/***	Environment variables	***/
char	*get_env_var(char *str);
char	**get_env_arr(void);
void	ft_env(void);

/***	CD	  ***/
void	ft_cd(t_table *table);

/***	ECHO	***/
void	ft_echo(t_table *table);

/***	EXIT	***/
void	ft_exit(t_table *table);

/***	EXPORT	***/
void	ft_export(char *args);

/***	PWD		***/
int		ft_pwd(void);

/***	UNSET	***/
void	ft_unset(t_table *table);

#endif