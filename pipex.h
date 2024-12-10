/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:21:17 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/10 23:13:56 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h> // for open, close, read, write, dup, dup2, access, fork, pipe, unlink
# include <fcntl.h> // for open flags
# include <stdlib.h> // for mallocs and exit
# include <stdio.h> // for perror()
# include <string.h> // for strerror()
# include <sys/types.h> // for pid_t
# include <sys/wait.h> // for wait, waitpid
# include <errno.h> // for errno

# define ERR_ARGS "Usage: ./pipex <file1> <cmd1> <cmd2> <file2>"
# define ERR_MALLOC "Failed to allocate memory."
# define ERR_CMD "Command not found."

typedef struct s_pipex
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**paths;
	char	**command_args;
	char	*command_path;
	int		infile;
	int		outfile;
}	t_pipex;

char	*get_path(char **envp);
char	*get_command(char **paths, char	*to_find);

#endif
