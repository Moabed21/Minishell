/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 06:03:41 by moabed            #+#    #+#             */
/*   Updated: 2026/03/22 09:43:17 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

void    shell_protection()
{
    if(!isatty(STDIN_FILENO))
        exit(3);
    if(!isatty(STDOUT_FILENO))
        exit(3);
}