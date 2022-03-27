/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:25:51 by fquist            #+#    #+#             */
/*   Updated: 2022/03/27 17:36:06 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

/***	Built_in exec	***/
int		built_in_exec(t_table *table);
bool	check_builtin(t_table *table);

/***	Environment variables	***/
char	*get_var_name(t_env *env);
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
bool	check_valid_var(char **str);

/***	PWD		***/
int		ft_pwd(void);

/***	UNSET	***/
void	ft_unset(t_table *table);

#endif