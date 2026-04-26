/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:17:10 by moabed            #+#    #+#             */
/*   Updated: 2026/04/26 06:41:33 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBS_H
# define LIBS_H

# define _POSIX_C_SOURCE 200809L
# define BUFFERSIZE 4096
// readline
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
// #define _DEFAULT_SOURCE
# include "../libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
#endif