/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shathaamarnah <shathaamarnah@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:06:11 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/03/14 19:46:33 by shathaamarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *tokenization(char *input)
{
    int i;
    int start;
    int status;
    t_token *token_list;
	t_token *eof;

	i = 0;
	start = 0;
	status = DEFAULT;
	token_list = NULL;
    while (input[i])
    {
        status = set_status(status, input, i);
        if (status == DEFAULT)
            start = save_word_or_op(&i, input, start, &token_list);
        i++;
    }
    if (status != DEFAULT)
    {
        if (status == DQUOTE)
            errmsg("unexpected EOF while looking for matching", "\"", 1);
        else if (status == SQUOTE)
            errmsg("unexpected EOF while looking for matching", "\'", 1);
        errmsg("syntax error", "unexpected end of file", 0);
        tokenlistclear(&token_list);
        return NULL;
    }
    eof = token_new(NULL, END);
    token_addback(&token_list, eof);
    return token_list;
}
