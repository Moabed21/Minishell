/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:30:35 by samarnah          #+#    #+#             */
/*   Updated: 2026/05/20 13:53:33 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/executionpart.h"
#include "headers/parsingpart.h"

int	expand_shell_name(char **result, int *i)
{
	*result = append_str(*result, "minishell");
	if (!*result)
		return (-1);
	*i += 2;
	return (0);
}

int	handle_quotes(char c, char *quote)
{
	if ((c == '\'' || c == '"') && *quote == 0)
	{
		*quote = c;
		return (1);
	}
	if (c == *quote)
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

int	handle_exit_status(char **result, int last_status)
{
	char	*status;

	status = ft_itoa(last_status);
	*result = append_str(*result, status);
	free(status);
	return (2);
}

int	expand_token(t_token **head, t_token *token, t_env *env, int last_status)
{
	char	*expanded;
	char	**words;
	t_token	*new_list;

	if (!token || !token->value)
		return (1);
	if (token->prev && token->prev->type == HEREDOC)
		return (1);
	expanded = expand_value(token->value, env, last_status, 0);
	if (!expanded)
		return (0);
	if (ft_strchr(expanded, ' ') && token->quoted == 0)
	{
		words = ft_split(expanded, ' ');
		new_list = create_tokens_from_words(words);
		insert_list(head, token, new_list);
		free(words);
		free(expanded);
		return (1);
	}
	free(token->value);
	token->value = expanded;
	return (1);
}

int	expand_tokens(t_token **tokens, t_env *env, int last_status)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *tokens;
	while (tmp)
	{
		next = tmp->next;
		if (!expand_token(tokens, tmp, env, last_status))
			return (0);
		tmp = next;
	}
	return (1);
}
