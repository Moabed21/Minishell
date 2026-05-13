/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingpart.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 06:41:01 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/05/13 19:01:09 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSINGPART_H
# define PARSINGPART_H

# include "libs.h"
# include "executionpart.h"

typedef struct s_env	t_env;

// token enum
typedef enum e_token_type
{
	WORD,
	PIPE,
	INPUT,
	TRUNC,
	APPEND,
	HEREDOC,
	SPACES,
	VAR,
	END
}					t_token_type;

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
}					t_cmd_type;

typedef enum e_status
{
	DEFAULT,
	SQUOTE,
	DQUOTE
}					t_status;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quoted;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

// redirection struct
typedef struct s_redir
{
	char			*filename;
	int				quoted;
	t_token_type	type;
	struct s_redir	*next;
}					t_redir;
// linked list for multiple redirs

typedef struct s_cmd
{
	int				fork_id;
	int				ret_stat;
	int				fd_in;
	int				fd_out;
	char			**args;
	t_cmd_type		cmd_type;
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;
t_cmd		*prepare_for_execution(char *input, t_env *env, int last_status);
//tokenization
t_token		*token_new(char *value, t_token_type type);
void		token_addback(t_token **list, t_token *new_node);
void		tokenlistclear(t_token **list);
void		del_one(t_token *node);
void		free_ptr(void **ptr);
int			save_op(t_token **token_lst, char *str, int index, int type);
int			save_word(t_token **token_lst, char *str, int index, int start);
int			is_operator(char *str, int i);
int			set_status(int status, char *str, int i);
int			save_word_or_op(int *i, char *str, int start, t_token **token_list);
int			has_quotes(char *str);
t_token		*tokenization(char *input);
//expansion
t_token		*insert_list(t_token **head, t_token *to_del, t_token *insert);
int			is_var_char(char c);
int			get_var_name_len(char *str);
char		*append_char(char *s, char c);
char		*append_str(char *s, char *to_add);
char		*expand_value(char *value, t_env *env, int last_status);
int			expand_token(t_token **head, t_token *token, t_env *env, int last_status);
int			expand_tokens(t_token **tokens, t_env *env, int last_status);
char		*get_env_value(char *key, t_env *env);
t_token		*create_tokens_from_words(char **words);
//parsing
t_cmd		*parsing(t_token *tokens);
int			arg_count(char **args);
int			add_arg(t_cmd *cmd, char *value);
char		**fill_args(t_token *tokens);
void		free_args(char **args);
t_cmd		*cmd_new(void);
void		cmd_addback(t_cmd **list, t_cmd *new_node);
t_token		*next_command(t_token *tokens);
void		free_cmds(t_cmd *cmds);
t_redir		*redir_new(t_token_type type, char *filename, int quoted);
void		redir_addback(t_redir **list, t_redir *new_node);
int			parse_redirs(t_cmd *cmd, t_token *tokens);
int			is_redir(t_token_type type);
void		free_redirs(t_redir *redir);
//check
int			check_consecutives(t_token **token_lst);
int			check_if_var(t_token **token_lst);
#endif