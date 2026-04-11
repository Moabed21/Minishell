/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-part.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:15:52 by moabed            #+#    #+#             */
/*   Updated: 2026/04/11 17:36:03 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_PART_H
#define EXECUTION_PART_H

#include "libs.h"
#include "parsing-part.h"

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

typedef struct s_env
{
	char *variable;
	struct s_env *next;
}t_env;
typedef struct s_exec
{
	int fd[2];		// for pipe()
	int last_status;
	char	**envp;
	t_env *first_env_node;
	t_cmd *cmds;
}t_exec;

//--------------signals--------------------
extern sig_atomic_t global_sig; //volatile tells the compiler "don't optimize reads/writes to this variable — it can change at any time (from a signal handler)."
// sig_atomic_t guarantees atomic read/write on all platforms.
void	execution(t_exec *shell);
void	interactive_signals(void);
void	default_signals();
//--------------builtins2-------------------
t_cmd_type	is_builtin(t_cmd *node);
void    exec_builtin(t_exec *shell, t_cmd *node, t_cmd_type type);
int		replace(char *target, t_env *env);
void    e_env(t_cmd *node,t_exec *shell);
void    e_exit(t_cmd *node,t_exec *shell);
//builtins
void    e_echo(t_cmd *node,t_exec *shell);
void    e_cd(t_cmd *node,t_exec *shell);
void    e_pwd(t_cmd *node,t_exec *shell);
void    e_export(t_cmd *node,t_exec *shell);
void    e_unset(t_cmd *node,t_exec *shell);
//io-redir
void	output_handle(t_redir *red, t_exec *minishell);
void	input_handle(t_redir *red, t_exec *minishell);
void	redir_handle(t_redir *redir, t_exec *minishell);
//env_utils
void	env_ruin(t_env **head);
t_env	*new_node(char * str);
t_env	*env_init(char **env);
void	env_add_last(t_env **env,char *target);
//utils
int		ft_strcmp(char *s1,char *s2);
int		has_no_equal(char *search);
void	error_display(int fd, char *cmd, char *right_end,t_exec *shell);
//utils2
char	*get_value(char *key,t_env *env);
char    **list_to_array(t_env *env);
void    free2d_array(char **arr);
void    shell_protection();
int		shell_init(char **env,t_exec *shell);
#endif