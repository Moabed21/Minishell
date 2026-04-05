/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:37:19 by moabed            #+#    #+#             */
/*   Updated: 2026/04/05 17:28:57 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

// done
void	e_echo(t_cmd *node, t_exec *shell)
{
	int	i;
	int	option;

	option = 0;
	i = 1;
	while (node->args[i] && !ft_strcmp(node->args[i], "-n"))
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
// TODO
void	e_cd(t_cmd *node, t_exec *shell)
{
	if (node->args[1])
	{
	}
	shell->last_status = 0;
}
// done
void	e_pwd(t_cmd *node, t_exec *shell)
{
	char	path[BUFFERSIZE];
	t_env	*ptr;

	ptr = shell->first_env_node;
	if (!getcwd(path, BUFFERSIZE))
	{
		while (ptr)
		{
			if (!ft_strncmp(ptr->variable, "PWD=", 4))
			{
				write(node->fd_out, ptr->variable + 4, ft_strlen(ptr->variable
						+ 4));
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
// done
void	e_export(t_cmd *node, t_exec *shell)
{
	int	i;
	int	loc;

	loc = 0;
	i = 1;
	if (!node->args[1])
		e_env(node, shell);
	else
	{
		while (node->args[i])
		{
			if (!replace(node->args[i], shell->first_env_node))
				env_add_last(&shell->first_env_node, node->args[i]);
			i++;
		}
	}
	shell->last_status = 0;
}
// TODO
void	e_unset(t_cmd *node, t_exec *shell)
{
	if (node->args[1])
	{
			
	}
	shell->last_status = 0;
}
