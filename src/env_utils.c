/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 09:15:25 by moabed            #+#    #+#             */
/*   Updated: 2026/03/22 09:16:13 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

t_env	*new_node(char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->variable = str;
	node->next = NULL;
	return (node);
}
void	env_ruin(t_env *head)
{
	t_env	*node;

	node = head;
	while (head->next != NULL)
	{
		node = node->next;
		free(head);
		head = node;
	}
	free(head);
}
t_env	*env_init(char **env)
{
	t_env *environment;
	t_env *head;
	int size;

	size = 0;
	head = environment;
	environment->variable = env[size];
	size++;
	while (env[size])
	{
		environment->next = new_node(env[size]);
		environment = environment->next;
		size++;
	}
	return (head);
}