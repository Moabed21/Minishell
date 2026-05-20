/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 07:52:31 by moabed            #+#    #+#             */
/*   Updated: 2026/05/16 16:06:11 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executionpart.h"

void	exec_builtin(t_exec *shell, t_cmd *node)
{
	if (!ft_strcmp("echo", node->args[0]))
		e_echo(node, shell);
	else if (!ft_strcmp("cd", node->args[0]))
		e_cd(node, shell);
	else if (!ft_strcmp("pwd", node->args[0]))
		e_pwd(node, shell);
	else if (!ft_strcmp("export", node->args[0]))
		e_export(node, shell);
	else if (!ft_strcmp("unset", node->args[0]))
		e_unset(node, shell);
	else if (!ft_strcmp("env", node->args[0]))
		e_env(node, shell);
	else if (!ft_strcmp("exit", node->args[0]))
		e_exit(node, shell);
}

void	e_env(t_cmd *node, t_exec *shell)
{
	t_env	*ptr;

	ptr = shell->first_env_node;
	while (ptr)
	{
		if (ptr->value)
		{
			write(node->fd_out, ptr->key, ft_strlen(ptr->key));
			write(node->fd_out, "=", 1);
			write(node->fd_out, ptr->value, ft_strlen(ptr->value));
			write(node->fd_out, "\n", 1);
		}
		ptr = ptr->next;
	}
	shell->last_status = 0;
}

static void	e_exit2(t_cmd *node, t_exec *shell)
{
	if (node->args[2])
	{
		write(2, "minishell: ", 12);
		error_display(STDERR_FILENO, node->args[0], ": too many arguments",
			shell);
		shell->last_status = 1;
		return ;
	}
	if (node->args[1])
		shell->last_status = ft_atoi(node->args[1]);
	else
		shell->last_status = 0;
	if (shell->cmds_count == 1)
		ruin_everything(shell);
	else
		free_current_cmd(&node);
	exit(shell->last_status);
}

void	e_exit(t_cmd *node, t_exec *shell)
{
	if (!node->next)
		write(2, "exit\n", 5);
	if (!node->args[1])
	{
		ruin_everything(shell);
		exit(0);
	}
	if (node->args[1] && not_a_num(node->args[1]))
	{
		write(2, "minishell: exit: ", 18);
		error_display(STDERR_FILENO, node->args[1],
			": numeric arguments required", shell);
		ruin_everything(shell);
		exit(2);
	}
	e_exit2(node, shell);
}
