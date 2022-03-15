/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 03:09:51 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/11 00:41:43 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_quoted_word(char *str, t_stringbuilder **sb)
{
	char	quote;
	int		i;

	i = 0;
	quote = str[i++];
	while (str[i] != quote)
	{
		sb_append_char(*sb, str[i]);
		i++;
	}
	return (++i);
}

static bool	check_quotes_closed(char *str, t_stringbuilder **sb)
{
	char	quote;

	quote = *str;
	while (*str)
	{
		if (*str == quote)
			return (true);
		str++;
	}
	sb_destroy(*sb);
	return (false);
}


static bool	check_valid_opt(char *opt)
{
	int	i;

	i = 0;
	if (ft_strncmp(opt, "-n", 2))
		return (false);
	i += 2;
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

/*
Checks if the first token is a valid option. 
If it is true, it will also skip the tokens,
from which the options are valid.
*/
static bool	check_opt(t_token **token)
{
	if (!check_valid_opt((*token)->name))
		return (false);
	while (*token)
	{
		if (!check_valid_opt((*token)->name))
			break ;
		(*token) = (*token)->next;
	}
	return (true);
}

/*
RET VAL -1 = error detected
RET VAL 0 = no errors detected and option is not activated
RET VAL 1 = no errors detected and option is activated
*/
int	define_echo_args(t_token *token, t_table **new)
{
	t_stringbuilder	*sb;
	int				res;

	res = 0;
	sb = sb_create();
	if (check_opt(&token))
		res = 1;
	while (token)
	{
		if (check_quotes(*token->name))
		{
			if (!check_quotes_closed(token->name, &sb))
				return (-1);
			get_quoted_word(token->name, &sb);
		}
		else
			sb_append_str(sb, token->name);
		sb_append_char(sb, ' ');
		token = token->next;
	}
	(*new)->args = sb_get_str(sb);
	sb_destroy(sb);
	return (res);
}

/////////////////////////////////////////////////////////////////////////
// int echo_parser(t_token *help, t_table **new)
// {
// 	bool	echo_opt_valid;

// 	echo_opt_valid = is_echo_opt_valid(help->name);
// 	if (echo_opt_valid)
// 	{
// 		(*new)->args = ft_strdup("-n");
// 		help = help->next;
// 		while (help)
// 		{
// 			if (!ft_strcmp(help->name, "-n"))
// 			{
// 				help = help->next;
// 				continue ;
// 			}
// 			else
// 				break ;
// 		}
// 	}
// 	else
// 	{
// 		if (*help->name == '$')
// 				(*new)->args = ft_strdup(get_env_var(help->name + 1));
// 		else
// 			(*new)->args = ft_strdup(help->name);
// 		help = help->next;
// 		while (help)
// 		{
// 			if (*help->name == '$')
// 				(*new)->args = str_join((*new)->args, " ", get_env_var(help->name + 1));
// 			else
// 				(*new)->args = str_join((*new)->args, " ", help->name);
// 			help = help->next;
// 		}
// 	}
// 	return (1);
// }