/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-part.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:15:52 by moabed            #+#    #+#             */
/*   Updated: 2026/03/31 07:20:03 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_PART_H
#define EXECUTION_PART_H

#include "parsing-part.h"
#include "libs.h"

typedef enum e_cmd_type
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_cmd_type;

int	global_sig;
void	execution(t_exec *minishell, char **envp);
void    signals_handling();
//env_utils
void env_ruin(t_env *head);
t_env *new_node(char * str);
t_env *env_init(char **env);
//utils
void    shell_protection();
//builder
t_cmd *builder();
typedef struct s_env
{
	char *variable;
	struct s_env *next;
}t_env;

typedef struct s_exec
{
	int fd[2];		// for pipe()
	t_env *first_env_node;
	t_cmd *cmds;
	int last_status;
}t_exec;


#endif