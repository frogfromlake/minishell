/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:37:24 by fquist            #+#    #+#             */
/*   Updated: 2022/03/11 00:32:49 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TODO: change env_var PWD after changing directory

void	change_pwd_var() //don't work
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = get_env_var("OLDPWD");
	new_pwd = get_env_var("PWD");
	// free(old_pwd);
	old_pwd = ft_strdup(new_pwd);
	// free(new_pwd);
	new_pwd = ft_strdup(getcwd(NULL, 0));
}

static char	*get_home_dir(void)
{
	t_env	*curr_env;

	curr_env = *(get_env(NULL));
	while (curr_env)
	{
		if (!ft_strncmp(curr_env->var, "HOME", 4))
			return (ft_strchr(curr_env->var, '/'));
		curr_env = curr_env->next;
	}
	return (NULL);
}

void	ft_cd(t_table *table)
{
	if (!table->args || !ft_strcmp(table->args, "~")
		|| !ft_strcmp(table->args, "--"))
	{
		if (table->args)
			free(table->args);
		table->args = ft_strdup(get_home_dir());
	}
	else if (!ft_strcmp(table->args, "-"))
	{
		free(table->args);
		table->args = ft_strdup(get_env_var("OLDPWD"));
	}
	if (chdir(table->args) == -1)
	{
		printf("bitchy snake shell: cd : %s: No such file or directory\n", table->args);
		return ;
	}
	change_pwd_var();
}
