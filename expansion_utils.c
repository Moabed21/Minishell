/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:41:12 by samarnah          #+#    #+#             */
/*   Updated: 2026/05/14 18:30:37 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/executionpart.h"
#include "headers/parsingpart.h"

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

static int	copy_str(char *dst, char *src, int start)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dst[start + i] = src[i];
		i++;
	}
	return (start + i);
}

char	*append_str(char *s, char *to_add)
{
	char	*new;
	int		len1;
	int		len2;
	int		i;

	len1 = 0;
	len2 = 0;
	if (s)
		len1 = ft_strlen(s);
	if (to_add)
		len2 = ft_strlen(to_add);
	new = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new)
		return (NULL);
	i = copy_str(new, s, 0);
	i = copy_str(new, to_add, i);
	new[i] = '\0';
	free(s);
	return (new);
}
