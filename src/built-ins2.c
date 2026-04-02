/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 07:52:31 by moabed            #+#    #+#             */
/*   Updated: 2026/04/02 21:26:53 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

void	e_env(t_cmd *node, t_exec *shell)
{
	t_env	*ptr;

	ptr = shell->first_env_node;
	while (ptr)
	{
		if (ft_strchr(ptr->variable, '='))
		{
			write(node->fd_out, ptr->variable, ft_strlen(ptr->variable));
			write(node->fd_out, "\n", 1);
		}
		ptr = ptr->next;
	}
	shell->last_status = 0;
}

void	e_exit(t_cmd *node, t_exec *shell)
{
	env_ruin(&shell->first_env_node);
	exit(shell->last_status);
	shell->last_status = 0;
}

t_cmd_type	is_builtin(t_cmd *node)
{
	t_cmd_type	type;

	type = NONE;
	if (!ft_strncmp("echo", node->args[0], 4))
		type = ECHO;
	if (!ft_strncmp("cd", node->args[0], 4))
		type = CD;
	if (!ft_strncmp("pwd", node->args[0], 3))
		type = PWD;
	if (!ft_strncmp("export", node->args[0], 6))
		type = EXPORT;
	if (!ft_strncmp("unset", node->args[0], 5))
		type = UNSET;
	if (!ft_strncmp("env", node->args[0], 3))
		type = ENV;
	if (!ft_strncmp("exit", node->args[0], 4))
		type = EXIT;
	return (type);
}

void	exec_builtin(t_exec *shell, t_cmd *node, t_cmd_type type)
{
	if (type == ECHO)
		e_echo(shell, node);
	if (type == CD)
		e_cd(shell, node);
	if (type == PWD)
		e_pwd(shell, node);
	if (type == EXPORT)
		e_export(shell, node);
	if (type == UNSET)
		e_unset(shell, node);
	if (type == ENV)
		e_env(shell, node);
	if (type == EXIT)
		e_exit(shell, node);
}
