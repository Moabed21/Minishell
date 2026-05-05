/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 18:24:19 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/05/05 17:17:30 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/parsingpart.h"

char	*expand_value(char *value, char **env, int last_status)
{
	char	*result;
	char	*name;
	char	*env_value;
	char	*status;
	char	quote;
	int		i;
	int		len;

	result = ft_strdup("");
	if (!result || !value)
		return (result);
	i = 0;
	quote = 0;
	while (value[i])
	{
		if ((value[i] == '\'' || value[i] == '"') && quote == 0)
		{
			quote = value[i];
			i++;
		}
		else if (value[i] == quote)
		{
			quote = 0;
			i++;
		}
		else if (value[i] == '$' && quote != '\'')
		{
			if (value[i + 1] == '?')
			{
				status = ft_itoa(last_status);
				result = append_str(result, status);
				free(status);
				i += 2;
			}
			else
			{
				len = get_var_name_len(&value[i + 1]);
				if (len == 0)
				{
					result = append_char(result, value[i]);
					i++;
				}
				else
				{
					name = ft_substr(value, i + 1, len);
					env_value = get_env_value(name, env);
					if (env_value)
						result = append_str(result, env_value);
					free(name);
					i += len + 1;
				}
			}
		}
		else
		{
			result = append_char(result, value[i]);
			i++;
		}
	}
	return (result);
}

int	expand_token(t_token **head, t_token *token, char **env, int last_status)
{
	char	*expanded;
	char	**words;
	t_token	*new_list;

	if (!token || !token->value)
		return (1);
	if (token->prev && token->prev->type == HEREDOC)
		return (1);
	expanded = expand_value(token->value, env, last_status);
	if (!expanded)
		return (0);
	// check if we need to split
	if (ft_strchr(expanded, ' ') && token->quoted == 0)
	{
		words = ft_split(expanded, ' ');
		new_list = create_tokens_from_words(words);
		insert_list(head, token, new_list);
		free(expanded);
		return (1);
	}
	free(token->value);
	token->value = expanded;
	return (1);
}

int	expand_tokens(t_token **tokens, char **env, int last_status)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (!expand_token(tokens, tmp, env, last_status))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

