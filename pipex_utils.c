/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:22:47 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/11 12:30:31 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initialise_px(t_pipex *px)
{
	px->fd[0] = -1;
	px->fd[1] = -1;
	px->pid1 = -1;
	px->pid2 = -1;
	px->infile = -1;
	px->outfile = -1;
	px->paths = NULL;
	px->command_args = NULL;
	px->command_path = NULL;
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
	if (px->fd[0] >= 0)
		close(px->fd[0]);
	if (px->fd[1] >= 0)
		close(px->fd[1]);
	if (px->paths)
		free_double_array(px->paths);
	if (px->command_args)
		free_double_array(px->command_args);
	if (px->command_path)
		free(px->command_path);
	if (px->infile >= 0)
		close(px->infile);
	if (px->outfile >= 0)
		close(px->outfile);
	ft_putstr_fd(context, 2);
	ft_putstr_fd(" error: ", 2);
	ft_putendl_fd(error_msg, 2);
	exit(EXIT_FAILURE);
}
