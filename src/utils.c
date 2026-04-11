/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 06:03:41 by moabed            #+#    #+#             */
/*   Updated: 2026/04/07 18:48:59 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	replace(char *target, t_env *env)
{
	int	i;

	i = 0;
	while (target[i] != '=' && target[i])
	{
		i++;
	}
	while (env)
	{
		if (!ft_strncmp(target, env->variable, i) && env->variable[i] == '=')
		{
			free(env->variable);
			env->variable = ft_strdup(target);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	has_no_equal(char *search)
{
	int	i;

	i = 0;
	while (search[i])
	{
		if (search[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	error_display(int fd, char *cmd, char *right_end, t_exec *shell)
{
	int	cmdlen;
	int	rightlen;

	rightlen = ft_strlen(right_end);
	cmdlen = ft_strlen(cmd);
	write(fd, "minishell: ", 12);
	write(fd, cmd, cmdlen);
	write(fd, right_end, rightlen);
	write(fd, "\n", 1);
	shell->last_status = 2;
}

char	*get_value(char *key, t_env *env)
{
	char *str;
	int	keylen;

	keylen = ft_strlen(key);
	while (env)
	{
		if (!ft_strncmp(key, env->variable, keylen) && env->variable[keylen] == '=')
		{
			str = env->variable + keylen + 1;
			break ;
		}
		env = env->next;
	}
	if (!str)
		return (NULL);
	return (str);
}