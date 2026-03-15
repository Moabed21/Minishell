/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-part.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:15:52 by moabed            #+#    #+#             */
/*   Updated: 2026/03/15 06:23:57 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_PART_H
#define EXECUTION_PART_H

#include "parsing-part.h"
#include "libs.h"

void    execution(t_cmd *cmds_list,char **envp);

#endif