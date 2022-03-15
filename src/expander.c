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

#include "../include/minishell.h"

// char	*expand_get_word_ws(char **input)
// {
// 	int		i;
// 	int		size;
// 	char	*res;

// 	size = 0;
// 	while ((*input)[size] && !check_whitespace((*input)[size])
// 		&& !check_metachar((*input)[size]) && !check_quotes((*input)[size]))
// 		size++;
// 	res = ft_calloc(size + 1, sizeof(char));
// 	if (!res)
// 		return (NULL);
// 	i = 0;
// 	while (i < size)
// 	{
// 		res[i] = (*input)[i];
// 		i++;
// 	}
// 	(*input) += i;
// 	return (res);
// }

// void	complex_expand(char **str)
// {
// 	t_stringbuilder *sb;
// 	char			*tmp;
// 	char			*env_var;

// 	sb = sb_create();
// 	tmp = *str;
// 	while (*tmp)
// 	{
// 		if (*tmp == '$')
// 		{
// 			tmp++;
// 			env_var = expand_get_word_ws(&tmp);
// 			sb_append_str(sb, get_env_var(env_var));
// 			free(env_var);
// 			env_var = NULL;
// 			continue ;
// 		}
// 		else
// 			sb_append_char(sb, *tmp);
// 		tmp++;
// 	}
// 	tmp = *str;
// 	*str = sb_get_str(sb);
// 	sb_destroy(sb);
// 	free(tmp);
// }

// int	expander(t_node **node)
// {
// 	t_node	*curr;
// 	t_token	*token;
// 	char	quote;
// 	char	*tmp;
// 	char	*env_var;

// 	curr = *node;
// 	while (curr)
// 	{
// 		if (!check_log_op(curr->type))
// 		{
// 			if (curr->tokens)
// 			{
// 				token = curr->tokens;
// 				while (token)
// 				{
// 					// handle case with here_doc redir - TODO: maybe do this on the lexer
// 					// if the delimiter has no quotes whatsoever, it should expand the env vars from the input/here_doc
// 					if (token->type == LESSLESS && check_quotes(*token->name) && check_quotes_closed(token->name))
// 					{
// 						quote = *token->name;
// 						tmp = token->name;
// 						token->name = ft_strtrim(token->name, &quote);
// 						free(tmp);
// 					}
// 					// trim single quotes and don't expand env var
// 					else if (check_quotes(*token->name) && *token->name == '\'' && check_quotes_closed(token->name)) // trim single quotes.
// 					{
// 						quote = *token->name;
// 						tmp = token->name;
// 						token->name = ft_strtrim(token->name, &quote);
// 						free(tmp);
// 					}
// 					// expand env var, if there a '$' char
// 					// TODO: handle case, if env var doesn't exist - empty str 
// 					// TODO: expand env vars on a double quoted string (complex expand)
// 					else if (*token->name == '$')
// 					{
// 						tmp = token->name;
// 						env_var = get_env_var(token->name + 1);
// 						if (!env_var)
// 						{
// 							token->prev->next = token->next;
// 							// free(token); //TODO: delete token from list
// 						}
// 						else //simple expand
// 							token->name = ft_strdup(env_var);
// 						free(tmp);
// 						tmp = NULL;
// 					}
// 					else if (*token->name == '\"' && check_quotes_closed(token->name)) // expand env vars in a double quoted string
// 					{
// 						// tmp = token->name;
// 						token->name = ft_strtrim(token->name, "\"");
// 						complex_expand(&token->name);
// 						if (!(*token->name))
// 							token->prev->next = token->next; //TODO: delete token from list
// 					}
// 					token = token->next;
// 				}
// 			}
// 		}
// 		curr = curr->next;
// 	}
// 	return (1);
// }