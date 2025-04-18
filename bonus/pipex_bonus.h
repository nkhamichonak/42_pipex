/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:57:34 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/19 17:54:30 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define ERR_ARG "Invalid argument count. Usage"
# define ERR_MALLOC "Failed to allocate memory"
# define ERR_CMD "Command not found"
# define ERR_LINE "Nothing to read"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		here_doc;
	int		command_count;
	int		command_index;
	char	**paths;
	char	**command_args;
	char	*command_path;
	int		child_status;
	bool	should_display_error;
	int		error_code;
}	t_pipex;

void	initialise_px(t_pipex *px);
int		min_arg_count(char *arg, t_pipex *px);
char	*get_path(char **envp);
void	free_double_array(char **str);
void	error_exit(char *context, char *error_msg, t_pipex *px);
void	get_files(int ac, char **argv, t_pipex *px);
char	**custom_split(char const *s, char c);

#endif
