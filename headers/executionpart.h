/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executionpart.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:15:52 by moabed            #+#    #+#             */
/*   Updated: 2026/05/10 16:02:01 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTIONPART_H
# define EXECUTIONPART_H

# include "parsingpart.h"

typedef struct s_env
{
	char						*value;
	char						*key;
	struct s_env				*next;
}								t_env;
typedef struct s_exec
{
	char						**envp;
	int							cmds_count;
	int							fd[2];
	int							last_status;
	t_env						*first_env_node;
	t_env						*sorted_env;
	t_cmd						*cmds;
}								t_exec;

//--------------signals--------------------
extern volatile sig_atomic_t	g_sig;
// volatile tells the compiler "don't optimize reads/writes to
// this variable — it can change at any time (from a signal handler)."
// sig_atomic_t guarantees atomic read/write on all platforms.
void							interactive_signals(void);
void							ignore_signals(void);
void							default_signals(void);
//--------------builtins2-------------------
void							exec_builtin(t_exec *shell, t_cmd *node);
void							cd_2(t_exec *shell, char *path, char *old_path);
void							e_env(t_cmd *node, t_exec *shell);
void							e_exit(t_cmd *node, t_exec *shell);
//--------------builtins--------------------
void							e_echo(t_cmd *node, t_exec *shell);
void							e_cd(t_cmd *node, t_exec *shell);
void							e_pwd(t_cmd *node, t_exec *shell);
void							e_export(t_cmd *node, t_exec *shell);
void							e_unset(t_cmd *node, t_exec *shell);
//--------------io-redir--------------------
void							output_handle(t_redir *red, t_cmd **cmd,
									int option);
void							input_handle(t_redir *red, t_cmd **current_cmd);
void							redir_handle(t_exec *shell, t_redir *red, t_cmd **cmd);
//--------------env_utils-------------------
void							env_ruin(t_env **head);
void							env_add_last(t_env **env, char *target);
t_env							*new_node(char *str);
t_env							*env_init(char **env);
//--------------utils-----------------------
int								ft_strcmp(char *s1, char *s2);
int								replace(char *key,char *value, t_env *env);
char							*get_value(char *key, t_env *env);
void							init_vals(t_exec *shell, t_cmd *cmds);
//-------------utils2----------------------
int								shell_init(char **env, t_exec *shell);
void							free2d_array(char **arr);
void							shell_protection(void);
void							check_cmds(t_cmd *cmds);
int								not_a_num(char *str);
//------------execution---------------------
char							**findpath(t_env *env);
void							execution(t_exec *shell);
void							ft_fork_pipe(t_exec *shell, t_cmd *node,
									int option);
void							wait_child(t_exec *shell, t_cmd *node);
//------------error-handle------------------
void							free_current_cmd(t_cmd **node);
void							ruin_everything(t_exec *shell);
void							error_display(int fd, char *cmd,
									char *right_end, t_exec *shell);
void							free_cmds_list(t_cmd **cmds);
//------------executeone--------------------
void							execute_one_cmd(t_exec *shell, t_cmd *node);
void							apply_fd(int fd1, int fd);
void							check_fds(t_cmd *node);
void							execute(t_exec *shell, t_cmd *node);
//-----------execute-multiple---------------
void							multiple_cmds(t_exec *shell, t_cmd *cmds_list);
//-----------heredoc------------------------
int								heredoc(t_exec *shell, char *delimiter, t_cmd **node, int quoted);
//-----------export-------------------------
t_env							*export_sorted(t_env *env);
#endif