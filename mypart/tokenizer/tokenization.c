/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shathaamarnah <shathaamarnah@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:06:11 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/04/22 18:23:53 by shathaamarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *tokenization(char *input)
{
    int i;
    int start;
    int status;
    t_token *token_list;

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
    if (i > start)
        save_word(&token_list, input, i, start);
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
    return token_list;
}
//main for testing tokenization phase
/*void print_list(t_token *head)
{
    t_token *current;
    current = head;
    while (current)
    {
        if (current->next)
            printf("%s-> ", current->value);
        else
            printf("%s", current->value);
        current = current->next;
    }
}

int main(){
    t_token *head = tokenization("\"ls -la | cat out\"");
    print_list(head);
    return (0);
}*/