/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:14:09 by natallia          #+#    #+#             */
/*   Updated: 2024/12/17 12:05:51 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	heredoc_child(char *limiter, t_pipex *px, int *fd)
{
	char	*line;

	close(fd[0]);
	while (true)
	{
		write(1, "pipe heredoc> ", 15);
		line = get_next_line(0);
		if (line == NULL)
			error_exit("Heredoc read", ERR_LINE, px);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	free(line);
	exit(EXIT_SUCCESS);
}

static void	handle_heredoc(char *limiter, t_pipex *px)
{
	int		fd[2];
	pid_t	pid_reader;

	if (pipe(fd) == -1)
		error_exit("Heredoc pipe", strerror(errno), px);
	pid_reader = fork();
	if (pid_reader == -1)
		error_exit("Heredoc fork", strerror(errno), px);
	if (pid_reader == 0)
		heredoc_child(limiter, px, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
	}
}

void	get_files(int ac, char **argv, t_pipex *px)
{
	if (!px->here_doc)
		px->outfile = open(argv[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		px->outfile = open(argv[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (px->outfile == -1)
		error_exit(argv[ac - 1], strerror(errno), px);
	if (!px->here_doc)
	{
		px->infile = open(argv[1], O_RDONLY);
		if (px->infile == -1)
			error_exit(argv[1], strerror(errno), px);
		dup2(px->infile, STDIN_FILENO);
		close(px->infile);
	}
	else
		handle_heredoc(argv[2], px);
}
