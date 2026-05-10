/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:13:53 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/05/10 19:49:07 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsingpart.h"
#include "../../headers/executionpart.h"


int	is_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || c == '_');
}

int	get_var_name_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_var_char(str[i]))
		i++;
	return (i);
}

char	*get_env_value(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*append_char(char *s, char c)
{
	char	*new;
	int		len;
	int		i;

	len = 0;
	if (s)
		len = ft_strlen(s);
	new = malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(s);
	return (new);
}

char	*append_str(char *s, char *to_add)
{
	char	*new;
	int		len1;
	int		len2;
	int		i;
	int		j;

	len1 = 0;
	len2 = 0;
	if (s)
		len1 = ft_strlen(s);
	if (to_add)
		len2 = ft_strlen(to_add);
	new = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		new[i] = s[i];
		i++;
	}
	j = 0;
	while (j < len2)
	{
		new[i] = to_add[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(s);
	return (new);
}
