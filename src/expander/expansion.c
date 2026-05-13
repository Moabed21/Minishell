/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 18:24:19 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/05/13 18:50:56 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsingpart.h"
#include "../../headers/executionpart.h"

static int	handle_quotes(char c, char *quote)
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

static int	handle_exit_status(char **result, int last_status)
{
	char	*status;

	status = ft_itoa(last_status);
	*result = append_str(*result, status);
	free(status);
	return (2);
}

static int	handle_env_var(char *value, int i, char **result, t_env *env)
{
	char	*name;
	char	*env_value;
	int		len;

	len = get_var_name_len(&value[i + 1]);
	if (len == 0)
	{
		*result = append_char(*result, value[i]);
		return (1);
	}
	name = ft_substr(value, i + 1, len);
	if (!name)
		return (-1);
	env_value = get_env_value(name, env);
	if (env_value)
		*result = append_str(*result, env_value);
	free(name);
	return (len + 1);
}

static int	handle_dollar(char *value, int i, char **result,
		t_env *env, int last_status)
{
	int	step;

	if (value[i + 1] == '?')
		return (handle_exit_status(result, last_status));
	step = handle_env_var(value, i, result, env);
	return (step);
}

char	*expand_value(char *value, t_env *env, int last_status)
{
	char	*result;
	char	quote;
	int		i;
	int		step;

	result = ft_strdup("");
	if (!result || !value)
		return (result);
	i = 0;
	quote = 0;
	while (value[i])
	{
		if (handle_quotes(value[i], &quote))
			i++;
		else if (value[i] == '$' && quote != '\'')
		{
			step = handle_dollar(value, i, &result, env, last_status);
			if (step == -1)
				return (free(result), NULL);
			i += step;
		}
		else
			result = append_char(result, value[i++]);
	}
	return (result);
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
	expanded = expand_value(token->value, env, last_status);
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

// void	print_list(t_token *head)
// {
// 	t_token	*current;

// 	current = head;
// 	while (current)
// 	{
// 		if (current->next)
// 			printf("%s-> ", current->value);
// 		else
// 			printf("%s", current->value);
// 		current = current->next;
// 	}
// }

// int	main(int ac, char **av, char **env)
// {
// 	t_token	*head;
// 	t_token	*head1;

// 	head = tokenization("echo \"$USER and $PATH\"");
// 	head1 = tokenization("$?");
// 	expand_tokens(&head, env, 0);
// 	expand_tokens(&head1, env, 0);
// 	print_list(head);
// 	print_list(head1);
// 	return (0);
// }
