/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:23:08 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/19 17:06:28 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	wait_for_children(t_pipex *px)
{
	waitpid(px->pid1, &px->child_one_status, 0);
	waitpid(px->pid2, &px->child_two_status, 0);
	if (WIFEXITED(px->child_one_status) && WEXITSTATUS(px->child_one_status))
		return (WEXITSTATUS(px->child_one_status));
	if (WIFEXITED(px->child_two_status) && WEXITSTATUS(px->child_two_status))
		return (WEXITSTATUS(px->child_two_status));
	return (0);
}

static void	second_child(char **argv, char **envp, t_pipex px)
{
	int		outfile;

	px.should_display_error = true;
	outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (outfile < 0)
		error_exit(argv[4], strerror(errno), &px);
	close(px.fd[1]);
	if (dup2(px.fd[0], STDIN_FILENO) == -1)
		error_exit("Second child dup", strerror(errno), &px);
	close(px.fd[0]);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error_exit("Second child dup", strerror(errno), &px);
	close(outfile);
	px.command_args = custom_split(argv[3], ' ');
	if (px.command_args == NULL)
		error_exit("Command args", ERR_MALLOC, &px);
	px.command_path = get_command(px.paths, px.command_args[0], &px);
	if (px.command_path == NULL)
	{
		px.error_code = 127;
		error_exit(argv[3], ERR_CMD, &px);
	}
	execve(px.command_path, px.command_args, envp);
	error_exit("Execve", strerror(errno), &px);
}

static void	first_child(char **argv, char **envp, t_pipex px)
{
	px.should_display_error = false;
	px.infile = open(argv[1], O_RDONLY);
	if (px.infile < 0)
		error_exit(argv[1], strerror(errno), &px);
	close(px.fd[0]);
	if (dup2(px.infile, STDIN_FILENO) == -1)
		error_exit("First child dup", strerror(errno), &px);
	close(px.infile);
	if (dup2(px.fd[1], STDOUT_FILENO) == -1)
		error_exit("First child dup", strerror(errno), &px);
	close(px.fd[1]);
	px.command_args = custom_split(argv[2], ' ');
	if (px.command_args == NULL)
		error_exit("Command args", ERR_MALLOC, &px);
	px.command_path = get_command(px.paths, px.command_args[0], &px);
	if (px.command_path == NULL)
		error_exit(argv[2], ERR_CMD, &px);
	execve(px.command_path, px.command_args, envp);
	error_exit("Execve", strerror(errno), &px);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		px;

	initialise_px(&px);
	if (argc != 5)
		error_exit("Usage: ./pipex file1 cmd1 cmd2 file2", ERR_ARGS, &px);
	if (pipe(px.fd) == -1)
		error_exit("Pipe", strerror(errno), &px);
	px.paths = ft_split(get_path(envp), ':');
	if (px.paths == NULL)
		error_exit("Paths", ERR_MALLOC, &px);
	px.pid1 = fork();
	if (px.pid1 == -1)
		error_exit("First child fork", strerror(errno), &px);
	if (px.pid1 == 0)
		first_child(argv, envp, px);
	px.pid2 = fork();
	if (px.pid2 == -1)
		error_exit("Second child fork", strerror(errno), &px);
	if (px.pid2 == 0)
		second_child(argv, envp, px);
	close(px.fd[0]);
	close(px.fd[1]);
	free_double_array(px.paths);
	return (wait_for_children(&px));
}
