/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:22:47 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/19 15:47:47 by natallia         ###   ########.fr       */
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
	px->child_one_status = 0;
	px->child_two_status = 0;
	px->should_display_error = true;
	px->error_code = 1;
}

char	*get_path(char **envp)
{
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (*envp + 5);
}

char	*get_command(char **paths, char	*to_find, t_pipex *px)
{
	char	*command_path;
	char	*temp;
	int		i;

	if (ft_strchr(to_find, '/') != NULL)
	{
		if (access(to_find, F_OK) == 0)
			return (ft_strdup(to_find));
		return (NULL);
	}
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (temp == NULL)
			error_exit("Command path temp", ERR_MALLOC, px);
		command_path = ft_strjoin(temp, to_find);
		free(temp);
		if (command_path == NULL)
			error_exit("Command path", ERR_MALLOC, px);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
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
	ft_putstr_fd("zsh: ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(context, 2);
	if (px->should_display_error)
		exit(px->error_code);
	else
		exit(EXIT_SUCCESS);
}
