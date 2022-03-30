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

#include "../../include/minishell.h"

static void	export_cd(char *args)
{
	t_env	**env;
	t_env	*existing;

	env = get_env(NULL);
	existing = check_var_existence(env, args);
	if (!existing)
		append_env(env, new_env(args));
	else
	{
		free(existing->var);
		existing->var = ft_strdup(args);
	}
}

static int	cd_error(char *str, int r_value)
{
	t_stringbuilder	*sb;
	char			*err_msg;

	sb = sb_create();
	sb_append_str(sb, "cd: ");
	sb_append_str(sb, str);
	sb_append_str(sb, ": No such file or directory");
	err_msg = sb_get_str(sb);
	sb_destroy(sb);
	error_msg(err_msg, r_value);
	free(err_msg);
	return (r_value);
}

static void	change_pwd_var(void)
{
	t_stringbuilder	*sb;
	char			*tmp;
	char			*tmp_pwd;

	sb = sb_create();
	sb_append_str(sb, "OLDPWD=");
	sb_append_str(sb, get_env_var("PWD"));
	tmp = sb_get_str(sb);
	export_cd(tmp);
	sb_clear(sb);
	sb_append_str(sb, "PWD=");
	tmp_pwd = getcwd(NULL, 0);
	sb_append_str(sb, tmp_pwd);
	free(tmp);
	free(tmp_pwd);
	tmp = sb_get_str(sb);
	export_cd(tmp);
	sb_destroy(sb);
	free(tmp);
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
		printf("%s\n", table->args);
	}
	if (chdir(table->args) == -1)
	{
		g_exit_status = cd_error(table->args, FAIL);
		return ;
	}
	change_pwd_var();
}
