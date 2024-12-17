/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:59:20 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/17 12:02:17 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	initialise_px(t_pipex *px)
{
	px->infile = -1;
	px->outfile = -1;
	px->here_doc = -1;
	px->command_count = 0;
	px->command_index = 0;
	px->paths = NULL;
	px->command_args = NULL;
	px->command_path = NULL;
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

char	*get_path(char **envp)
{
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (*envp + 5);
}

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

void	error_exit(char *context, char *error_msg, t_pipex *px)
{
	if (px->infile >= 0)
		close(px->infile);
	if (px->outfile >= 0)
		close(px->outfile);
	if (px->paths)
		free_double_array(px->paths);
	if (px->command_args)
		free_double_array(px->command_args);
	if (px->command_path)
		free(px->command_path);
	ft_putstr_fd("zsh: ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(context, 2);
	exit(EXIT_FAILURE);
}
