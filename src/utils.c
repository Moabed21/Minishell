/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 06:03:41 by moabed            #+#    #+#             */
/*   Updated: 2026/04/05 16:01:05 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

void	shell_protection(void)
{
	if (!isatty(STDIN_FILENO))
		exit(3);
	if (!isatty(STDOUT_FILENO))
		exit(3);
}
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}

int	replace(char *target, t_env *env)
{
	int i;

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