/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:37:19 by moabed            #+#    #+#             */
/*   Updated: 2026/05/13 10:48:14 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executionpart.h"

t_env	*new_clone_node(t_env *env)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(env->key);
	node->value = ft_strdup(env->value);
	node->next = NULL;
	if (!node->key && node->value)
	{
		free(node->value);
		free(node);
	}
	if (node->key && !node->value)
	{
		free(node->key);
		free(node);
	}
	if (!node->key && !node->value)
		free(node);
	if (!node)
		return (NULL);
	return (node);
}

t_env	*env_clone(t_env *env)
{
	t_env	*env_recover;
	t_env	*ptr;
	t_env	*clone_head;

	env_recover = env;
	clone_head = new_clone_node(env_recover);
	if (!clone_head)
		return (NULL);
	ptr = clone_head;
	env_recover = env_recover->next;
	while (env_recover)
	{
		clone_head->next = new_clone_node(env_recover);
		clone_head = clone_head->next;
		env_recover = env_recover->next;
	}
	return (ptr);
}
int	list_size(t_env *env)
{
	t_env	*ptr;
	int		i;

	i = 0;
	ptr = env;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}
t_env	*export_sorted(t_env *env)
{
	int		size;
	int		i;
	int		j;
	t_env	*ptr;

	i = 0;
	ptr = env;
	size = list_size(env);
	while (i < size)
	{
		j = i + 1;
		while (j < size - j)
		{
			if ()
			{
			}
			j++;
		}
		i++;
	}
}

t_env	*sort_workspace(t_env *env)
{
	t_env	*cloned_env;
	t_env	*ptr;
	int		size;

	cloned_env = env_clone(env);
	if (!cloned_env)
		return (NULL);
	ptr = export_sorted(cloned_env);
	return (ptr);
}
void	no_args(t_exec *shell, t_cmd *node)
{
	t_env	*ptr;
	t_env	*ptr2;

	ptr2 = shell->first_env_node;
	shell->sorted_env = sort_workspace(ptr2);
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

int	has_args(t_exec *shell, t_cmd *node)
{
	int	has_error;
	int	i;

	i = 1;
	has_error = 0;
	while (node->args[i])
	{
		if (ft_isalpha(node->args[i][0]) || node->args[i][0] == '_')
			env_add_last(&shell->first_env_node, node->args[i]);
		else
		{
			write(2, "minishell: export: `", 21);
			write(2, node->args[i], ft_strlen(node->args[i]));
			write(2, ": not a valid identifier\n", 26);
			has_error++;
		}
		i++;
	}
	return (has_error);
}

void	e_export(t_cmd *node, t_exec *shell)
{
	int	has_error;

	has_error = 0;
	if (!node->args[1])
		no_args(shell, node);
	else
		has_error = has_args(shell, node);
	if (has_error)
		shell->last_status = 1;
	else
		shell->last_status = 0;
}
