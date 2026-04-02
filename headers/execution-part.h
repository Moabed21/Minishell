/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-part.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:15:52 by moabed            #+#    #+#             */
/*   Updated: 2026/04/02 21:30:50 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_PART_H
#define EXECUTION_PART_H

#include "parsing-part.h"
#include "libs.h"

typedef enum e_cmd_type
{
	NONE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_cmd_type;

typedef struct s_exec
{
	int fd[2];		// for pipe()
	t_env *first_env_node;
	t_cmd *cmds;
	int last_status;
}t_exec;

typedef struct s_env
{
	char *variable;
	struct s_env *next;
}t_env;

int	global_sig;
// shell_init
void    shell_init(t_env *env);

void	execution(t_exec *shell, t_env *env);
void    signals_handling();
//builtins2
t_cmd_type	is_builtin(t_cmd *node);
void    exec_builtin(t_exec *shell, t_cmd *node, t_cmd_type type);
//builtins
void    e_echo(t_cmd *node,t_exec *shell);
void    e_cd(t_cmd *node,t_exec *shell);
void    e_pwd(t_cmd *node,t_exec *shell);
void    e_export(t_cmd *node,t_exec *shell);
void    e_unset(t_cmd *node,t_exec *shell);
void    e_env(t_cmd *node,t_exec *shell);
void    e_exit(t_cmd *node,t_exec *shell);

//env_utils
void	env_ruin(t_env **head);
t_env	*new_node(char * str);
t_env	*env_init(char **env);
void	env_add_last(t_env **env,char *target);
//utils
void    shell_protection();

#endif