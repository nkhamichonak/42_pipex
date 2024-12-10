/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:21:17 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/10 12:58:56 by nkhamich         ###   ########.fr       */
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

# define ERR_ARGS "Bad arguments. Usage: ./pipex <file1> <cmd1> <cmd2> <file2>"

#endif