/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 12:41:21 by moabed            #+#    #+#             */
/*   Updated: 2026/05/18 08:46:17 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executionpart.h"

int	replace(char *key, char *value, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(key, env->key))
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(value);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

char	*get_value(char *key, t_env *env)
{
	char	*str;

	str = NULL;
	while (env)
	{
		if (!ft_strcmp(key, env->key))
		{
			str = env->value;
			break ;
		}
		env = env->next;
	}
	if (!str)
		return (NULL);
	return (str);
}

void	cd_2(t_exec *shell, char *path, char *old_path)
{
	if (!path || chdir(path) == -1)
	{
		if (!path)
			write(2, "minishell: cd: HOME not set\n", 28);
		else
			perror("minishell: cd");
		shell->last_status = 1;
		return ;
	}
	replace("OLDPWD", old_path, shell->first_env_node);
	if (getcwd(old_path, BUFFERSIZE))
		replace("PWD", old_path, shell->first_env_node);
	else
		replace("PWD", path, shell->first_env_node);
	shell->last_status = 0;
}

void	e_cd(t_cmd *node, t_exec *shell)
{
	char	*path;
	char	old_path[BUFFERSIZE];
	char	*current_pwd;

	if (node->args[1] && node->args[2])
	{
		error_display(2, "cd", ": too many arguments", shell);
		shell->last_status = 1;
		return ;
	}
	if (!getcwd(old_path, BUFFERSIZE))
	{
		current_pwd = get_value("PWD", shell->first_env_node);
		if (current_pwd)
			ft_strlcpy(old_path, current_pwd, BUFFERSIZE);
	}
	if (!node->args[1])
		path = get_value("HOME", shell->first_env_node);
	else
		path = node->args[1];
	cd_2(shell, path, old_path);
}
