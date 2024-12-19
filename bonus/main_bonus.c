/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:55:06 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/18 21:02:28 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*get_command(char **paths, char	*to_find)
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

static void	child_process(char **argv, char **envp, t_pipex px, int *fd)
{
	bool	is_last;
	int		argv_index;

	close(fd[0]);
	is_last = (px.command_count == 1);
	argv_index = 2 + px.here_doc + px.command_index;
	if (!is_last && dup2(fd[1], STDOUT_FILENO) == -1)
		error_exit("Dup", strerror(errno), &px);
	else if (is_last && dup2(px.outfile, STDOUT_FILENO) == -1)
		error_exit("Dup", strerror(errno), &px);
	close(fd[1]);
	px.command_args = ft_split(argv[argv_index], ' ');
	if (px.command_args == NULL)
		error_exit("Command args", ERR_MALLOC, &px);
	px.command_path = get_command(px.paths, px.command_args[0]);
	if (px.command_path == NULL)
		error_exit(argv[argv_index], ERR_CMD, &px);
	execve(px.command_path, px.command_args, envp);
	error_exit("Execve", strerror(errno), &px);
}

static void	handle_pipeline(char **argv, char **envp, t_pipex *px)
{
	bool	is_last;
	int		fd[2];
	int		pid;

	is_last = (px->command_count == 1);
	if (!is_last && pipe(fd) == -1)
		error_exit("Pipe", strerror(errno), px);
	pid = fork();
	if (pid == -1)
		error_exit("Fork", strerror(errno), px);
	if (pid == 0)
		child_process(argv, envp, *px, fd);
	else
	{
		close(fd[1]);
		if (!is_last && dup2(fd[0], STDIN_FILENO) == -1)
			error_exit("Dup", strerror(errno), px);
		close(fd[0]);
		px->command_count--;
		waitpid(pid, &px->child_status, 0);
		if (px->child_status != 0)
			return (free_double_array(px->paths), px->child_status);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		px;

	initialise_px(&px);
	if (argc < min_arg_count(argv[1], &px))
	{
		if (px.here_doc)
			error_exit("./pipex here_doc LIMITER cmd cmd1 file", ERR_ARG, &px);
		else
			error_exit("./pipex file1 cmd1 cmd2 ... cmdn file2", ERR_ARG, &px);
	}
	get_files(argc, argv, &px);
	px.command_count = argc - 3 - px.here_doc;
	px.paths = ft_split(get_path(envp), ':');
	if (px.paths == NULL)
		error_exit("Paths", ERR_MALLOC, &px);
	while (px.command_count)
	{
		handle_pipeline(argv, envp, &px);
		px.command_index++;
	}
	free_double_array(px.paths);
	return (0);
}
