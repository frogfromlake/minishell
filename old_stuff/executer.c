/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 13:26:17 by fquist            #+#    #+#             */
/*   Updated: 2022/02/22 17:38:51 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// implement stderr redirection
// implement input from parsing
void	execute()
{
	int	id;
	int	i;
	int	fdin;
	int	fdout;
	int	tmpin;
	int tmpout;
	int	fdpipe[2];
	extern char	**environ;

	// save in/out
	tmpin = dup(0);
	tmpout = dup(1);
	i = 0;

	// set initial input
	if (infile)
		fdin = open(infile, O_RDONLY);
	else
		fdin = dup(tmpin); // use default input
	while (i < nbrOfSimpleCommands)
	{
		// redirect input
		dup2(fdin, 0);
		close(fdin);
		// setup output
		if (i == nbrOfSimpleCommands - 1)
		{
			if (outfile)
				fdout = open(outfile, O_WRONLY);
			else // use default
				fdout = dup(tmpout);
		}
		else // mot last simple cmd, create pipe
		{
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		// redirect output
		dup2(fdout, 1);
		close(fdout);
		// Create child prc
		id = fork();
		if (id == 0) 
		{ 
			//child 
			execve(path, cmd, environ);
			perror("execve");
			exit(1);
		}
		else if (id < 0) 
		{ 
			perror("fork"); 
			return ;
		}
		i++;
	// Parent shell continue 
	} // for
	// restore in/out defaults
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	
	if (!background)
	{ 
		// wait for last process/cmd
		waitpid(id, NULL, 0);
	}
}// execute 
