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
#define LIBS_H

#define _POSIX_C_SOURCE 200809L
#define BUFFERSIZE 4096
#define SUCCESS 0
#define FAILURE 1

/* ── ANSI Colors ─────────────────────────────────────────── */
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define DIM "\033[2m"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define BRED "\033[1;31m"
#define BGREEN "\033[1;32m"
#define BYELLOW "\033[1;33m"
#define BBLUE "\033[1;34m"
#define BMAGENTA "\033[1;35m"
#define BCYAN "\033[1;36m"
#define BWHITE "\033[1;97m"
#include <stdio.h>
// readline
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
// #define _DEFAULT_SOURCE
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#endif