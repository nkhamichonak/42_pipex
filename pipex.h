/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:21:17 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/11 12:34:11 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

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

void	initialise_px(t_pipex *px);
void	free_double_array(char **str);
void	error_exit(char *context, char *error_msg, t_pipex *px);

#endif
