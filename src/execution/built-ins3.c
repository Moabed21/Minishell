/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 12:40:54 by moabed            #+#    #+#             */
/*   Updated: 2026/05/09 22:24:15 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executionpart.h"

void	unset_2(t_env **head)
{
    free((*head)->key);
    free((*head)->value);
}

void	e_unset(t_cmd *node, t_exec *shell)
{
	int	i;
    t_env   *prev;
    t_env   *curr;

	i = 0;
	while (node->args[++i])
	{
        ptr = shell->first_env_node;
        while (ptr)
        {
            if(!ft_strcmp(node->args[i],ptr->key))
                unset_2(&ptr);
            ptr = ptr->next;
        }
        
        node->args[i];
	}
	shell->last_status = 0;
}

// to be checked
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
