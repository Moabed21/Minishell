/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:29:33 by samarnah          #+#    #+#             */
/*   Updated: 2026/05/13 19:32:57 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsingpart.h"
#include "../../headers/executionpart.h"

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

static int	expand_status(int *i, char **result, int last_status)
{
	int	step;

	step = handle_exit_status(result, last_status);
	if (step == -1)
		return (-1);
	*i += step;
	return (0);
}

static int	expand_env(char *value, int *i, char **result, t_env *env)
{
	int	step;

	step = handle_env_var(value, *i, result, env);
	if (step == -1)
		return (-1);
	*i += step;
	return (0);
}

static void	expand_char(char *value, int *i, char **result)
{
	*result = append_char(*result, value[*i]);
	(*i)++;
}

char	*expand_value(char *value, t_env *env, int last_status, int i)
{
	char	*result;
	char	quote;

	result = ft_strdup("");
	if (!result || !value)
		return (result);
	quote = 0;
	while (value[i])
	{
		if (handle_quotes(value[i], &quote))
			i++;
		else if (value[i] == '$' && quote != '\'' && value[i + 1] == '?')
		{
			if (expand_status(&i, &result, last_status) == -1)
				return (free(result), NULL);
		}
		else if (value[i] == '$' && quote != '\'')
		{
			if (expand_env(value, &i, &result, env) == -1)
				return (free(result), NULL);
		}
		else
			expand_char(value, &i, &result);
	}
	return (result);
}
