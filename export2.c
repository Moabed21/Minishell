/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 07:54:00 by moabed            #+#    #+#             */
/*   Updated: 2026/05/18 13:41:51 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/executionpart.h"

static int	valid_identifier(char *str)
{
	int		i;
	char	*equal;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	equal = ft_strchr(str, '=');
	i = 1;
	while (str[i] && &str[i] != equal)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	export_one(t_exec *shell, char *arg)
{
	char	*equal;
	char	*key;

	equal = ft_strchr(arg, '=');
	if (equal)
	{
		key = ft_substr(arg, 0, equal - arg);
		if (!key)
			return ;
		if (!replace(key, equal + 1, shell->first_env_node))
			env_add_last(&shell->first_env_node, arg);
		free(key);
	}
	else
	{
		if (!get_value(arg, shell->first_env_node))
			env_add_last(&shell->first_env_node, arg);
	}
}

void	no_args(t_exec *shell, t_cmd *node)
{
	t_env	*ptr;

	shell->sorted_env = sort_workspace(shell->first_env_node);
	if (!shell->sorted_env)
		return ;
	ptr = shell->sorted_env;
	while (ptr)
	{
		write(node->fd_out, "declare -x ", 11);
		write(node->fd_out, ptr->key, ft_strlen(ptr->key));
		if (ptr->value)
		{
			write(node->fd_out, "=\"", 2);
			write(node->fd_out, ptr->value, ft_strlen(ptr->value));
			write(node->fd_out, "\"", 1);
		}
		write(node->fd_out, "\n", 1);
		ptr = ptr->next;
	}
	env_ruin(&shell->sorted_env);
}

void	e_export(t_cmd *node, t_exec *shell)
{
	int	has_error;
	int	i;

	has_error = 0;
	if (!node->args[1])
	{
		no_args(shell, node);
		shell->last_status = 0;
		return ;
	}
	i = 1;
	while (node->args[i])
	{
		if (valid_identifier(node->args[i]))
			export_one(shell, node->args[i]);
		else
		{
			write(2, "minishell: export: `", 20);
			write(2, node->args[i], ft_strlen(node->args[i]));
			write(2, "': not a valid identifier\n", 27);
			has_error = 1;
		}
		i++;
	}
	shell->last_status = has_error;
}
