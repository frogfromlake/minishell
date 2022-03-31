/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:20:25 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/30 23:48:38 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char *argv[], char **environ)
{
	t_node	*head;
	t_table	*table;

	(void) argc;
	(void) argv;
	g_exit_status = 0;
	head = NULL;
	table = NULL;
	get_env(environ);
	init_snake_shell(&head, &table);
	return (g_exit_status);
}
