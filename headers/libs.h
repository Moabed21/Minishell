/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:17:10 by moabed            #+#    #+#             */
/*   Updated: 2026/04/29 06:26:05 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBS_H
# define LIBS_H

# define _POSIX_C_SOURCE 200809L
# define BUFFERSIZE 4096
// readline
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
// #define _DEFAULT_SOURCE
# include "../src/libft/libft.h"
# include <sys/wait.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
#endif