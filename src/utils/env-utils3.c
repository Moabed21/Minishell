/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 09:15:25 by moabed            #+#    #+#             */
/*   Updated: 2026/05/08 20:36:03 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executionpart.h"

void	new_node2(t_env *node, char *str)
{
	char	*equal_ptr;

	equal_ptr = ft_strchr(str, '=');
	if (equal_ptr)
	{
		node->key = ft_substr(str, 0, equal_ptr - str);
		node->value = ft_strdup(equal_ptr + 1);
	}
	else
	{
		node->key = ft_strdup(str);
		node->value = NULL;
	}
}

t_env	*new_node(char *str)
{
	t_env	*node;
	char	*equal;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	new_node2(node, str);
	equal = ft_strchr(str, '=');
	if (!node->key || (equal && !node->value))
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

void	env_ruin(t_env **head)
{
	t_env	*node;

	node = (*head);
	if (!(*head))
		return ;
	while ((*head)->next != NULL)
	{
		node = node->next;
		free((*head)->key);
		free((*head)->value);
		free((*head));
		(*head) = node;
	}
	free((*head)->key);
	free((*head)->value);
	free((*head));
	*head = NULL;
}

t_env	*env_init(char **env)
{
	int		size;
	t_env	*head;
	t_env	*ptr;

	size = 1;
	if (!env || !env[0])
		return (NULL);
	ptr = new_node(env[0]);
	if (!ptr)
		return (NULL);
	head = ptr;
	while (env[size])
	{
		ptr->next = new_node(env[size]);
		if (!ptr->next)
			return (head);
		ptr = ptr->next;
		size++;
	}
	return (head);
}

void	env_add_last(t_env **env, char *target)
{
	t_env	*ptr;
	t_env	*new;

	if (!*env)
		return ;
	new = new_node(target);
	if (!new)
		return ;
	ptr = (*env);
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	ptr->next = new;
}
