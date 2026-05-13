/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:06:11 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/05/13 18:35:42 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsingpart.h"

int	has_quotes(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static t_token	*handle_unclosed_quotes(t_token **token_list, int status)
{
	if (status == DQUOTE)
		errmsg("unexpected EOF while looking for matching", "\"", 1);
	else if (status == SQUOTE)
		errmsg("unexpected EOF while looking for matching", "\'", 1);
	errmsg("syntax error", "unexpected end of file", 0);
	tokenlistclear(token_list);
	return (NULL);
}

t_token	*tokenization(char *input)
{
	int		i;
	int		start;
	int		status;
	t_token	*token_list;

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
		return (handle_unclosed_quotes(&token_list, status));
	return (token_list);
}
