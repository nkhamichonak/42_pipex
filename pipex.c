/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:23:08 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/09 16:34:25 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	error_exit(int num_error)
{
	if (num_error == 1)
	{
		ft_putendl_fd("Error: Bad arguments.", 2);
		ft_putendl_fd("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>", 2);
	}
	exit(EXIT_FAILURE);
}

void	execute_child(char **argv, char **envp, int pipe_fd)
{
	
}

void	execute_parent(char **argv, char **envp, int pipe_fd)
{
	
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;
	
	if (argc != 5)
		error_exit(1);
	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		execute_child(argv, envp, pipe_fd);
	else
	{
		wait(NULL);
		execute_parent(argv, envp, pipe_fd);
	}
	return (0);
}
