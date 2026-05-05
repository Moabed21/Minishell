/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:41:05 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/05/05 16:45:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsingpart.h"

int	save_op(t_token **token_lst, char *str, int index, int type)
{
	int		i;
	char	*op;
	t_token	*new;

	i = 0;
	if (type == APPEND || type == HEREDOC)
		op = malloc(sizeof(char) * 3);
	else
		op = malloc(sizeof(char) * 2);
	if (!op)
		return (0);
	while ((type == APPEND || type == HEREDOC) && i < 2)
		op[i++] = str[index++];
	while (!(type == APPEND || type == HEREDOC) && i < 1)
		op[i++] = str[index++];
	op[i] = '\0';
	new = token_new(op, type);
	if (!new)
	{
		free(op);
		return (0);
	}
	token_addback(token_lst, new);
	return (1);
}

int	save_word(t_token **token_lst, char *str, int index, int start)
{
	int		i;
	char	*word;
	t_token	*new;

	i = 0;
	word = malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return (0);
	while (start < index)
	{
		word[i++] = str[start++];
	}
	word[i] = '\0';
	new = token_new(word, WORD);
	if (!new)
	{
		free(word);
		return (0);
	}
	new->quoted = has_quotes(word);
	token_addback(token_lst, new);
	return (1);
}

int	is_operator(char *str, int i)
{
	if (((str[i] > 8 && str[i] < 14) || str[i] == 32))
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '<')
		return (INPUT);
	else if (str[i] == '>')
		return (TRUNC);
	else if (str[i] == '\0')
		return (END);
	return (0);
}

int	set_status(int status, char *str, int i)
{
	if (str[i] == '\'' && status == DEFAULT)
		status = SQUOTE;
	else if (str[i] == '\"' && status == DEFAULT)
		status = DQUOTE;
	else if (str[i] == '\'' && status == SQUOTE)
		status = DEFAULT;
	else if (str[i] == '\"' && status == DQUOTE)
		status = DEFAULT;
	return (status);
}

int save_word_or_op(int *i, char *str, int start, t_token **token_list)
{
    int type;

    type = is_operator(str, (*i));
    if (type)
    {
        if (*i > start)
    		save_word(token_list, str, *i, start);
        if (type == APPEND || type == HEREDOC
            || type == PIPE || type == INPUT
            || type == TRUNC || type == END)
        {
            save_op(token_list, str, (*i), type);
            if (type == APPEND || type == HEREDOC)
                (*i)++;
        }
        start = (*i) + 1;
    }
    return start;
}
