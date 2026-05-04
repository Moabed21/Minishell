/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 07:52:31 by moabed            #+#    #+#             */
/*   Updated: 2026/05/04 11:23:53 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executionpart.h"

void	cd_2(t_exec *shell, char *path, char *old_path)
{
	char	*tmp;

	if (!path || chdir(path) == -1)
	{
		if (!path)
			write(2, "minishell: cd: path not set\n", 29);
		else
			perror("minishell: cd");
		shell->last_status = 1;
		return ;
	}
	tmp = ft_strjoin("OLDPWD=", old_path);
	replace(tmp, shell->first_env_node);
	free(tmp);
	getcwd(old_path, BUFFERSIZE);
	tmp = ft_strjoin("PWD=", old_path);
	replace(tmp, shell->first_env_node);
	free(tmp);
	shell->last_status = 0;
}

int	not_a_num(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

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
	write(2, "exit\n", 5);
	if (node->args[1] && not_a_num(node->args[1]))
	{
		error_display(2, node->args[0], ": numeric arguments required", shell);
		shell->last_status = 2;
		return ;
	}
	if (node->args[2])
	{
		error_display(2, node->args[0], ": too many arguments", shell);
		shell->last_status = 2;
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
