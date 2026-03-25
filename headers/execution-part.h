/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-part.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:15:52 by moabed            #+#    #+#             */
/*   Updated: 2026/03/24 19:00:28 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_PART_H
#define EXECUTION_PART_H

#include "parsing-part.h"
#include "libs.h"

int	global_sig;
void	execution(t_exec *minishell, char **envp);
void    signals_handling();
//env_utils
void env_ruin(t_env *head);
t_env *new_node(char * str);
t_env *env_init(char **env);
//utils
void    shell_protection();

typedef struct s_env
{
	char *variable;
	struct s_env *next;
}t_env;

typedef struct s_exec
{
	t_env *first_env_node;
	t_cmd *cmds;
	int last_status;
}t_exec;


#endif