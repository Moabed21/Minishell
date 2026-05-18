/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executionpart.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:15:52 by moabed            #+#    #+#             */
/*   Updated: 2026/05/18 15:50:57 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTIONPART_H
# define EXECUTIONPART_H

# include "parsingpart.h"
# include "libs.h"

typedef struct s_cmd			t_cmd;
typedef struct s_redir			t_redir;
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
	int							sigint_received;
	int							sigquit_received;
	int							last_status;
	t_env						*first_env_node;
	t_env						*sorted_env;
	t_cmd						*cmds;
}								t_exec;

extern volatile sig_atomic_t	g_sig;

void							interactive_signals(void);
void							ignore_signals(void);
void							default_signals(void);
void							exec_builtin(t_exec *shell, t_cmd *node);
void							e_env(t_cmd *node, t_exec *shell);
void							e_exit(t_cmd *node, t_exec *shell);
void							e_cd(t_cmd *node, t_exec *shell);
void							e_echo(t_cmd *node, t_exec *shell);
void							e_pwd(t_cmd *node, t_exec *shell);
void							e_unset(t_cmd *node, t_exec *shell);
void							output_handle(t_redir *red, t_cmd **cmd,
									int option);
void							input_handle(t_redir *red, t_cmd **current_cmd);
void							redir_handle(t_redir *red,
									t_cmd **cmd);
void							env_ruin(t_env **head);
void							env_add_last(t_env **env, char *target);
t_env							*new_node(char *str);
t_env							*env_init(char **env);
int								ft_strcmp(char *s1, char *s2);
int								replace(char *key, char *value, t_env *env);
char							*get_value(char *key, t_env *env);
void							init_vals(t_exec *shell, t_cmd *cmds);
int								shell_init(char **env, t_exec *shell);
void							free2d_array(char **arr);
void							shell_protection(void);
void							check_cmds(t_cmd *cmds);
int								not_a_num(char *str);
char							**findpath(t_env *env);
void							execution(t_exec *shell);
void							ft_fork_pipe(t_exec *shell, t_cmd *node,
									int option);
void							wait_child(t_exec *shell, t_cmd *node);
void							apply_fd(int fd1, int fd);
void							free_current_cmd(t_cmd **node);
void							ruin_everything(t_exec *shell);
void							error_display(int fd, char *cmd,
									char *right_end, t_exec *shell);
void							free_cmds_list(t_cmd **cmds);
void							errmsg(char *errmsg, char *detail, int check);
void							execute_one_cmd(t_exec *shell, t_cmd *node);
void							check_fds(t_cmd *node);
void							execute(t_exec *shell, t_cmd *node);
void							multiple_cmds(t_exec *shell, t_cmd *cmds_list);
int								heredoc(t_exec *shell, char *delimiter,
									t_cmd **node, int quoted);
void							e_export(t_cmd *node, t_exec *shell);
t_env							*sort_workspace(t_env *env);
void							no_args(t_exec *shell, t_cmd *node);
int								preprocess_heredocs(t_exec *shell, t_cmd *cmds);
void							close_pipe(t_exec *shell);
void							print_signal_messages(t_exec *shell);
void							wait_all(t_exec *shell);
void							handle_fds(t_exec *shell, t_cmd *node);
void							close_all_saved_fds(t_cmd *cmds);
#endif
