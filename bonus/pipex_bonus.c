/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:55:06 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/11 17:06:42 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_heredoc(char *arg, t_pipex *px)
{
	
}

void	get_files(int ac, char **argv, t_pipex *px)
{
	if (px->here_doc)
		px->outfile = open(argv[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		px->outfile = open(argv[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->outfile == -1)
		error_exit("Outfile", strerror(errno), px);
	if (px->here_doc)
		handle_heredoc(argv[2], px);
	else
	{
		px->infile = open(argv[1], O_RDONLY);
		if (px->infile == -1)
			error_exit("Infile", strerror(errno), px);
	}
}

int	min_arg_count(char *arg, t_pipex *px)
{
	int		min_count;

	min_count = 5;
	if (arg && ft_strncmp("here_doc", arg, 9) == 0)
	{
		px->here_doc = 1;
		min_count++;
	}
	else
		px->here_doc = 0;
	return (min_count);

}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		px;

	// initialise_px(&px);
	if (argc < min_arg_count(argv[1], &px))
		error_exit("Input", ERR_ARGS, &px);
	get_files(argc, argv, &px);
		
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
