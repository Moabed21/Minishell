/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 09:15:25 by moabed            #+#    #+#             */
/*   Updated: 2026/04/05 15:44:30 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

t_env	*new_node(char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->variable = ft_strdup(str);
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
		free((*head)->variable);
		free((*head));
		(*head) = node;
	}
	free((*head)->variable);
	free((*head));
	*head = NULL;
}

t_env	*env_init(char **env)
{
	int		size;
	t_env	*head;
	t_env	*ptr;

	size = 0;
	ptr = new_node(env[size]);
	head = ptr;
	size++;
	while (env[size])
	{
		ptr->next = new_node(env[size]);
		ptr = ptr->next;
		size++;
	}
	return (head);
}

void	env_add_last(t_env **env, char *target)
{
	t_env	*ptr;

	if (!*env)
		return ;
	ptr = (*env);
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	ptr->next = new_node(target);
}
