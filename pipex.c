/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:23:08 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/10 14:57:18 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	error_exit(char *error_msg, int *fd)
{
	if (fd != NULL)
	{
		close(fd[0]);
		close(fd[1]);
	}
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(error_msg, 2);
	exit(EXIT_FAILURE);
}

void	execute_first_child(char **argv, char **envp, int fd)
{
	int		infile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error_exit(strerror(errno), fd);
}

void	execute_second_child(char **argv, char **envp, int fd)
{
	int		outfile;

	outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (outfile < 0)
		error_exit(strerror(errno), fd);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	
	if (argc != 5)
		error_exit(ERR_ARGS, NULL);
	if (pipe(fd) == -1)
		error_exit(strerror(errno), NULL);
	pid1 = fork();
	if (pid1 == -1)
		error_exit(strerror(errno), fd);
	if (pid1 == 0)
		execute_first_child(argv, envp, fd);
	pid2 = fork();
	if (pid2 == -1)
		error_exit(strerror(errno), fd);
	if (pid2 == 0)
		execute_second_child(argv, envp, fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

