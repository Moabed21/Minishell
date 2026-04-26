/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:37:19 by moabed            #+#    #+#             */
/*   Updated: 2026/04/26 13:26:17 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

// done
void	e_echo(t_cmd *node, t_exec *shell)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	node->cmd_type = ECHO;
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

void	e_cd(t_cmd *node, t_exec *shell)
{
	char	*path;
	char	old_path[BUFFERSIZE];

	node->cmd_type = CD;
	if (node->args[2])
	{
		error_display(2, "cd", ": too many arguments", shell);
		return ;
	}
	getcwd(old_path, BUFFERSIZE);
	if (!node->args[1])
		path = get_value("HOME", shell->first_env_node);
	else if (!ft_strcmp("-", node->args[1]))
		path = get_value("OLDPWD", shell->first_env_node);
	else
		path = node->args[1];
	cd_2(shell, node, path, old_path);
}

void	e_pwd(t_cmd *node, t_exec *shell)
{
	char	path[BUFFERSIZE];
	t_env	*ptr;

	node->cmd_type = PWD;
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

void	e_export(t_cmd *node, t_exec *shell)
{
	int	i;
	int	loc;

	node->cmd_type = EXPORT;
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

void	e_unset(t_cmd *node, t_exec *shell)
{
	int	i;

	i = 0;
	node->cmd_type = UNSET;
	while (node->args[++i])
	{
		if (has_no_equal(node->args[i]))
			unset_2(&shell->first_env_node, node->args[i]);
	}
	shell->last_status = 0;
}
