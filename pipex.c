/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:23:08 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/11 12:26:17 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

char	*get_path(char **envp)
{
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (*envp + 5);
}

char	*get_command(char **paths, char	*to_find)
{
	char	*command_path;
	char	*temp;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (temp == NULL)
			return (NULL);
		command_path = ft_strjoin(temp, to_find);
		free(temp);
		if (command_path == NULL)
			return (NULL);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
		i++;
	}
	return (NULL);
}

void	second_child(char **argv, char **envp, t_pipex px)
{
	int		outfile;

	outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (outfile < 0)
		error_exit("Outfile", strerror(errno), &px);
	close(px.fd[1]);
	if (dup2(px.fd[0], STDIN_FILENO) == -1)
		error_exit("Dup", strerror(errno), &px);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error_exit("Dup", strerror(errno), &px);
	close(outfile);
	px.command_args = ft_split(argv[3], ' ');
	if (px.command_args == NULL)
		error_exit("Command args", ERR_MALLOC, &px);
	px.command_path = get_command(px.paths, px.command_args[0]);
	if (px.command_path == NULL)
		error_exit("Command path", ERR_CMD, &px);
	if (execve(px.command_path, px.command_args, envp) == -1)
		error_exit("Execve", strerror(errno), &px);
}

void	first_child(char **argv, char **envp, t_pipex px)
{
	px.infile = open(argv[1], O_RDONLY);
	if (px.infile < 0)
		error_exit("Infile", strerror(errno), &px);
	close(px.fd[0]);
	if (dup2(px.infile, STDIN_FILENO) == -1)
		error_exit("Dup", strerror(errno), &px);
	close(px.infile);
	if (dup2(px.fd[1], STDOUT_FILENO) == -1)
		error_exit("Dup", strerror(errno), &px);
	px.command_args = ft_split(argv[2], ' ');
	if (px.command_args == NULL)
		error_exit("Command args", ERR_MALLOC, &px);
	px.command_path = get_command(px.paths, px.command_args[0]);
	if (px.command_path == NULL)
		error_exit("Command path", ERR_CMD, &px);
	if (execve(px.command_path, px.command_args, envp) == -1)
		error_exit("Execve", strerror(errno), &px);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		px;

	initialise_px(&px);
	if (argc != 5)
		error_exit("Invalid input", ERR_ARGS, &px);
	if (pipe(px.fd) == -1)
		error_exit("Pipe", strerror(errno), &px);
	px.paths = ft_split(get_path(envp), ':');
	if (px.paths == NULL)
		error_exit("Paths", ERR_MALLOC, &px);
	px.pid1 = fork();
	if (px.pid1 == -1)
		error_exit("Fork", strerror(errno), &px);
	if (px.pid1 == 0)
		first_child(argv, envp, px);
	px.pid2 = fork();
	if (px.pid2 == -1)
		error_exit("Fork", strerror(errno), &px);
	if (px.pid2 == 0)
		second_child(argv, envp, px);
	close(px.fd[0]);
	close(px.fd[1]);
	waitpid(px.pid1, NULL, 0);
	waitpid(px.pid2, NULL, 0);
	return (free_double_array(px.paths), 0);
}
