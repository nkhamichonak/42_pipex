/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:23:08 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/10 23:20:04 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	free_double_array(char **str)
{
	int		i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}
void	error_exit(char *context, char *error_msg, t_pipex px)
{
	if (px.fd)
	{
		if (px.fd[0] >= 0)
			close(px.fd[0]);
		if (px.fd[1] >= 0)
			close(px.fd[1]);
	}
	if (px.paths)
		free_double_array(px.paths);
	if (px.command_args)
		free_double_array(px.command_args);
	if (px.command_path)
		free_double_array(px.command_path);
	if (px.infile >= 0)
		close(px.infile);
	if (px.outfile >= 0)
		close(px.outfile);
	ft_putstr_fd(context, 2);
	ft_putstr_fd(" error: ", 2);
	ft_putendl_fd(error_msg, 2);
	exit(EXIT_FAILURE);
}

void	first_child(char **argv, char **envp, t_pipex px)
{
	px.infile = open(argv[1], O_RDONLY);
	if (px.infile < 0)
		error_exit("Infile", strerror(errno), px);
	close(px.fd[0]);
	if (dup2(px.infile, STDIN_FILENO) == -1)
		error_exit("Dup", strerror(errno), px);
	close(px.infile);
	if (dup2(px.fd[1], STDOUT_FILENO) == -1)
		error_exit("Dup", strerror(errno), px);
	px.command_args = ft_split(argv[2], ' ');
	if (px.command_args == NULL)
		error_exit("Command args", ERR_MALLOC, px);
	px.command_path = get_command(px.paths, px.command_args[0]);
	if (px.command_path == NULL)
		error_exit("Command path", ERR_CMD, px);
	if (execve(px.command_path, px.command_args, envp) == -1)
		error_exit("Execve", strerror(errno), px);
}

void	second_child(char **argv, char **envp, t_pipex px)
{
	int		outfile;

	outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (outfile < 0)
		error_exit("Outfile", strerror(errno), px);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		px;

	if (argc != 5)
		error_exit("Invalid input", ERR_ARGS, px);
	if (pipe(px.fd) == -1)
		error_exit("Pipe", strerror(errno), px);
	px.paths = ft_split(get_path(envp), ':');
	if (px.paths == NULL)
		error_exit("Paths", ERR_MALLOC, px);
	px.pid1 = fork();
	if (px.pid1 == -1)
		error_exit("Fork", strerror(errno), px);
	if (px.pid1 == 0)
		first_child(argv, envp, px);
	px.pid2 = fork();
	if (px.pid2 == -1)
		error_exit("Fork", strerror(errno), px);
	if (px.pid2 == 0)
		second_child(argv, envp, px);
	waitpid(px.pid1, NULL, 0);
	waitpid(px.pid2, NULL, 0);
	return (cleanup(px), 0);
}
