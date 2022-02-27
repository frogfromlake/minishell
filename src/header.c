/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:37:49 by fquist            #+#    #+#             */
/*   Updated: 2022/02/27 18:06:31 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_shell(void)
{
	printf("\033[1;32m");
	printf("\n");
	printf("	                         __\n");
	printf("	           ---_ ...... _/_ -\n");
	printf("	          /  .      ./ .'*\\ \n");
	printf("	          : '         /__-'   \\.\n");
	printf("	         /                     )\n");
	printf("	       _/                  >   .\n");
	printf("	     /   .   .       _.-\" /  .'\n");
	printf("	     \\           __/\"     /.'\n");
	printf("	       \\ '--  .-\" /     //'\n");
	printf("	        \\|  \\ | /     //\n");
	printf("	             \\:     //\n");
	printf("	          `\\/     //\n");
	printf("	           \\__`\\/ /\n");
	printf("	               \\_|\n");
	printf("\n");
	printf("\n");
	printf("  __|               |             __|  |           |  | \n");
	printf("\\__ \\    \\    _` |  | /   -_)   \\__ \\    \\    -_)  |  | \n");
	printf("____/ _| _| \\__,_| _\\_\\ \\___|   ____/ _| _| \\___| _| _| \n");
	printf("_______________________________________________________\n");
	printf("\n\n\n\e[0m");
}
