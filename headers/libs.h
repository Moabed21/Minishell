/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:17:10 by moabed            #+#    #+#             */
/*   Updated: 2026/05/14 18:29:03 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBS_H
# define LIBS_H

# define _POSIX_C_SOURCE 200809L
# define BUFFERSIZE 4096
# define SUCCESS 0
# define FAILURE 1
# include <stdio.h>
// readline
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
// #define _DEFAULT_SOURCE
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
#endif