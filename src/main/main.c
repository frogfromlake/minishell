/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:20:25 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/27 20:08:36 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//bash tester.sh m 
//bash tester.sh -f cmds/test.sh

static char	*ft_append(char *line, char c)
{
	int		length;
	int		i;
	char	*longer;

	if (line == NULL)
		return (NULL);
	length = ft_strlen(line);
	longer = ft_calloc(length + 2, sizeof(char));
	if (longer == NULL)
		free(line);
	i = 0;
	while (line && line[i] != '\0')
	{
		longer[i] = line[i];
		i++;
	}
	if (longer)
		longer[i] = c;
	if (line)
		free(line);
	return (longer);
}


static int	ex_get_next_line(char **line, int fd)
{
	char	buffer;
	int		flag;

	if (line == NULL)
		return(-1);
	*line = malloc(1);
	if (*line == NULL)
		return(-1);
	*line[0] = '\0';
	while ((flag = read(fd, &buffer, 1) > 0))
	{
		if (buffer == '\n')
			break ;
		*line = ft_append(*line, buffer);
	}
	return(flag);
}

// TODO: implement return values for cmds.
// TODO: syntax control on env and if just name (w/o '='), then it should not print on "env' just on "export"
// TODO: set correct exit_status on parser!!

int	g_exit_status;

static int	check_empty_input(char *input)
{
	int	i;

	i = 0;
	while (check_whitespace(input[i]))
		i++;
	if (input[i] == '\0')
		return (1);
	else
		return (0);
}

char	*get_prompt(void)
{
	t_stringbuilder	*prompt;
	char			*path;
	char			*ret;

	prompt = sb_create();
	path = getcwd(NULL, 0);
	sb_append_str(prompt, CYAN);
	sb_append_str(prompt, ft_strrchr(path, '/'));
	sb_append_str(prompt, "\033[0;32m °º¤ø,¸,ø¤º°`°º¤ø(ಠ_ಠ)┌∩┐ ");
	sb_append_str(prompt, GREEN);
	sb_append_str(prompt, "@");
	sb_append_str(prompt, getenv("USER"));
	sb_append_str(prompt, "$ \e[0m");
	ret = sb_get_str(prompt);
	sb_destroy(prompt);
	free(path);
	return (ret);
}

static void	bitchy_snake_shell(t_node **head, t_table **table)
{
	char	*read;
	char	*tmp;
	int		s_out = dup(STDOUT_FILENO);
	int		s_in = dup(STDIN_FILENO);

	// print_header();
	// system("(afplay mp3/welcome.mp3&)");
	// system("(afplay mp3/snake.mp3&)");
	// system("afplay mp3/error2.mp3");
	while (true)
	{	
		change_termios(true);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_handler);
		// tmp = get_prompt();
		if (isatty(0))
			read = readline(tmp);
		else
			if(ex_get_next_line(&read, 0) == 0)
				read = NULL ;
		// free(tmp);
		if (read != NULL && ft_strcmp(read, ""))
		{
			add_history(read);
			if (!check_empty_input(read))
			{
				lexer(head, read);
				// print_nodes(*head);
				expander(head);
				// print_nodes(*head);
				parser(head, table);
				// print_cmd_table(*table);
				if (g_exit_status == SUCCESS)
				{
					change_termios(false);
					exec_loop(*table);
				}
			}
			free_node(head);
			free_table(table);
		}
		free(read);
		dup2(s_in, STDIN_FILENO);
		dup2(s_out, STDOUT_FILENO);
		if (!read)
		{
			// printf("exit\n");
			break ;
		}
	}
}

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
	bitchy_snake_shell(&head, &table);
	return (0);
}
