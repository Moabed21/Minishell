/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing-part.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 06:41:01 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/04/02 10:13:12 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_PART_H
# define PARSING_PART_H
#include "libs.h"

//token enum
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
}	t_token_type;

typedef enum e_status
{
	DEFAULT,
	SQUOTE,
	DQUOTE
}	t_status;

typedef struct s_token
{
	char            *value;
	t_token_type    type;
	struct s_token  *prev;
	struct s_token  *next;
}   t_token;

//redirection struct
typedef struct s_redir
{
	t_token_type    type;
	int				file_d; //every redir has a file for either input or output , to deal with him we need an fd
	char            *filename;
	struct s_redir  *next;     // linked list for multiple redirs
} t_redir;

//command struct
typedef struct s_cmd
{
	int fork_id;	// every command will be handled by one child
	int				ret_stat;
	int				fd_in;
	int				fd_out;
	char			**args;
	t_cmd_type 		cmd_type; // to see if the command is from built-ins
	t_redir         *redir;
	struct s_cmd    *next; // for pipes
}   t_cmd;

//functions
t_token 	*token_new(char *value, t_token_type type);
void 		token_addback(t_token **list, t_token *new_node);
void 		tokenlistclear(t_token **list);
void 		del_one(t_token *node);
void        free_ptr(void **ptr);
t_token	    *insert_list(t_token **head, t_token *to_del, t_token *insert);
int			save_op(t_token **token_lst, char *str, int index, int type);
int			save_word(t_token **token_lst, char *str, int index, int start);
int			is_operator(char *str, int i);
int			set_status(int status, char *str, int i);
int			save_word_or_op(int *i, char *str, int start, t_token **token_list);
//utils
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s);
void		ft_putendl_fd(char *s, int fd);
size_t		ft_strlen(const char *s);
void		errmsg(char *errmsg, char *detail, int check);
#endif