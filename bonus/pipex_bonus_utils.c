/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:59:20 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/11 15:28:52 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	ft_putstr_fd(context, 1);
	ft_putstr_fd(" error: ", 1);
	ft_putendl_fd(error_msg, 2);
	exit(EXIT_FAILURE);
}