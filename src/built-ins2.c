/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 07:52:31 by moabed            #+#    #+#             */
/*   Updated: 2026/04/20 11:46:40 by moabed           ###   ########.fr       */
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
int	not_a_num(t_cmd *node, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	e_exit(t_cmd *node, t_exec *shell)
{
	if (node->args[1] && not_a_num(node, node->args[1]))
	{
		error_display(2, node->args[0], ": too many arguments",
			shell);
		shell->last_status = 2;
		return ;
	}
	if (node->args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		shell->last_status = 2;
		return ;
	}
	if (node->args[1])
		shell->last_status = ft_atoi(node->args[1]);
	else
		shell->last_status = 0;
	env_ruin(&shell->first_env_node);
	exit(shell->last_status);
}

t_cmd_type	is_builtin(t_cmd *node)
{
	t_cmd_type	type;

	type = NONE;
	if (!ft_strcmp("echo", node->args[0]))
		type = ECHO;
	if (!ft_strcmp("cd", node->args[0]))
		type = CD;
	if (!ft_strcmp("pwd", node->args[0]))
		type = PWD;
	if (!ft_strcmp("export", node->args[0]))
		type = EXPORT;
	if (!ft_strcmp("unset", node->args[0]))
		type = UNSET;
	if (!ft_strcmp("env", node->args[0]))
		type = ENV;
	if (!ft_strcmp("exit", node->args[0]))
		type = EXIT;
	return (type);
}

void	exec_builtin(t_exec *shell, t_cmd *node, t_cmd_type type)
{
	if (type == ECHO)
		e_echo(node, shell);
	if (type == CD)
		e_cd(node, shell);
	if (type == PWD)
		e_pwd(node, shell);
	if (type == EXPORT)
		e_export(node, shell);
	if (type == UNSET)
		e_unset(node, shell);
	if (type == ENV)
		e_env(node, shell);
	if (type == EXIT)
		e_exit(node, shell);
}
