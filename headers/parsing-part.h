/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing-part.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 06:41:01 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/03/06 19:16:29 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_PART_H
# define PARSING_PART_H

//token struct
typedef enum e_token_type
{
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HEREDOC
}   t_token_type;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
}   t_token;

//redirection struct
typedef struct s_redir
{
    t_token_type    type;
    char            *filename;
    struct s_redir  *next;     // linked list for multiple redirs
} t_redir;

//command struct
typedef struct s_cmd
{
    char            **args;
    t_redir         *redir;
    struct s_cmd    *next; // for pipes
}   t_cmd;

#endif