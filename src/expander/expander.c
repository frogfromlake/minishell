/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:47:19 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/13 00:41:03 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: expand $?

static char *get_word_envname(char **tmp)
{
	t_stringbuilder	*sb;
	char			*env_name;
	int				i;

	i = 0;
	sb = sb_create();
	while (ft_is_alpha((*tmp)[i]) || (*tmp)[i] == '_')
		i++;
	sb_append_strn(sb, *tmp, i);
	env_name = sb_get_str(sb);
	sb_destroy(sb);
	*tmp += i;
	return (env_name);
}

void	dollar_expand(t_stringbuilder **sb, char **tmp)
{
	char	*env_name;

	(*tmp)++;
	if (ft_is_alpha(**tmp) || **tmp == '_')
	{
		env_name = get_word_envname(tmp);
		sb_append_str(*sb, get_env_var(env_name));
		free(env_name);
	}
	else
	{
		if (**tmp == '$')
		{
			sb_append_str(*sb, "$$");
			(*tmp)++;
		}
		else if (**tmp == '?')
		{
			sb_append_int(*sb, g_exit_status);
			(*tmp)++;
		}
		else //if (!(**tmp))
			sb_append_char((*sb), '$');
	}
}

void	dquote_expand(t_stringbuilder **sb, char **tmp)
{
	sb_append_char(*sb, **tmp);
	(*tmp)++;
	while (**tmp && **tmp != DQUOTE)
	{
		if (**tmp == '$')
		{
			dollar_expand(sb, tmp);
			continue ;
		}
		else
			sb_append_char(*sb, **tmp);
		(*tmp)++;
	}
}

void	squote_no_expand(t_stringbuilder **sb, char **tmp)
{
	int	i;

	i = 1;
	while ((*tmp)[i] && (*tmp)[i] != SQUOTE)
		i++;
	if ((*tmp)[i] == SQUOTE)
		i++;
	sb_append_strn(*sb, *tmp, i);
	*tmp += i;
}

void	expand(t_token **token)
{
	t_stringbuilder	*sb;
	char			*tmp;

	sb = sb_create();
	tmp = (*token)->name;
	while (*tmp)
	{
		if (*tmp == '$')
			dollar_expand(&sb, &tmp);
		else if (*tmp == DQUOTE)
			dquote_expand(&sb, &tmp);
		else if (*tmp == SQUOTE)
			squote_no_expand(&sb, &tmp);
		else
		{
			sb_append_char(sb, *tmp);
			tmp++;
		}
	}
	free((*token)->name);
	(*token)->name = sb_get_str(sb);
	sb_destroy(sb);
}

int	expander(t_node **head)
{
	t_node	*node;
	t_token	*token;

	node = *head;
	while (node)
	{
		if (!check_log_op(node->type) && node->type != LESSLESS && node->tokens)
		{
			token = node->tokens;
			while (token)
			{
				if (ft_strchr(token->name, '$')
					|| ft_strchr(token->name, SQUOTE)
					|| ft_strchr(token->name, DQUOTE))
					expand(&token);
				token = token->next;
			}
		}
		node = node->next;
	}
	return (1);
}
