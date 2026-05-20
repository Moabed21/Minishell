/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:37:19 by moabed            #+#    #+#             */
/*   Updated: 2026/05/14 18:30:11 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/executionpart.h"

t_env	*new_clone_node(t_env *env)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(env->key);
	if (env->value)
		node->value = ft_strdup(env->value);
	else
		node->value = NULL;
	node->next = NULL;
	if (!node->key || (env->value && !node->value))
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
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
		ptr->next = new_clone_node(env_recover);
		if (!ptr->next)
			break ;
		ptr = ptr->next;
		env_recover = env_recover->next;
	}
	return (clone_head);
}

static void	swap_data(t_env *a, t_env *b)
{
	char	*tmp;

	tmp = a->key;
	a->key = b->key;
	b->key = tmp;
	tmp = a->value;
	a->value = b->value;
	b->value = tmp;
}

void	export_sorted(t_env *env)
{
	int		swapped;
	t_env	*ptr;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = env;
		while (ptr && ptr->next)
		{
			if (ft_strcmp(ptr->key, ptr->next->key) > 0)
			{
				swap_data(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
	}
}

t_env	*sort_workspace(t_env *env)
{
	t_env	*cloned_env;

	cloned_env = env_clone(env);
	if (!cloned_env)
		return (NULL);
	export_sorted(cloned_env);
	return (cloned_env);
}
