/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-part.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:15:52 by moabed            #+#    #+#             */
/*   Updated: 2026/03/22 12:12:55 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_PART_H
#define EXECUTION_PART_H

#include "parsing-part.h"
#include "libs.h"

void    execution(t_cmd *cmds_list, char **envp);
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
	//if im executing a command , what do i need ?
	//1) fd[2] the pipe, the fork id, the return status, the env i have to loop on
	//to execute, a file descriptor for opening and closing
	int fd[2];
	int fork_id;
	int ret_stat;
	int input_file_d;
	int output_file_d;
	t_env *first_env_node;
}t_exec;


#endif