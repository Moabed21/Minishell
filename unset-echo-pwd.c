/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset-echo-pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 12:40:54 by moabed            #+#    #+#             */
/*   Updated: 2026/05/14 18:30:24 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/executionpart.h"

static void	unset_2(t_env **head, t_env *target, t_env *prev)
{
	if (!prev)
		*head = (*head)->next;
	else
		prev->next = target->next;
	free(target->key);
	free(target->value);
	free(target);
}

void	e_unset(t_cmd *node, t_exec *shell)
{
	int		i;
	t_env	*curr;
	t_env	*prev;

	i = 0;
	while (node->args[++i])
	{
		curr = shell->first_env_node;
		prev = NULL;
		while (curr)
		{
			if (!ft_strcmp(curr->key, node->args[i]))
			{
				unset_2(&shell->first_env_node, curr, prev);
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
	}
	shell->last_status = 0;
}

static int	is_all_n(char *s)
{
	int	i;

	i = 1;
	if (!s || s[0] != '-' || !s[1])
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	e_echo(t_cmd *node, t_exec *shell)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	while (node->args[i] && is_all_n(node->args[i]))
	{
		i++;
		option = 1;
	}
	while (node->args[i])
	{
		write(node->fd_out, node->args[i], ft_strlen(node->args[i]));
		if (node->args[i + 1])
			write(node->fd_out, " ", 1);
		i++;
	}
	if (option == 0)
		write(node->fd_out, "\n", 1);
	shell->last_status = 0;
}

void	e_pwd(t_cmd *node, t_exec *shell)
{
	char	path[BUFFERSIZE];
	t_env	*ptr;

	ptr = shell->first_env_node;
	if (!getcwd(path, BUFFERSIZE))
	{
		while (ptr)
		{
			if (!ft_strcmp(ptr->key, "PWD"))
			{
				write(node->fd_out, ptr->value, ft_strlen(ptr->value));
				break ;
			}
			ptr = ptr->next;
		}
	}
	else
		write(node->fd_out, path, ft_strlen(path));
	write(node->fd_out, "\n", 1);
	shell->last_status = 0;
}
