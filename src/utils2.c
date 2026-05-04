/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:23:48 by moabed            #+#    #+#             */
/*   Updated: 2026/05/04 09:57:27 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executionpart.h"

volatile sig_atomic_t g_sig = 0;

void	shell_protection(void)
{
	if (!isatty(STDIN_FILENO))
		exit(3);
	if (!isatty(STDOUT_FILENO))
		exit(3);
}

int	shell_init(char **env, t_exec *shell)
{
	shell_protection();
	shell->envp = env;
	shell->first_env_node = env_init(env);
	if (!shell->first_env_node)
		return (1);
	shell->last_status = 0;
	return (0);
}

void	free2d_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	unset_2(t_env **head, char *name)
{
	t_env	**curr;
	t_env	*tmp;
	int		len;

	len = ft_strlen(name);
	curr = head;
	while (*curr)
	{
		if (!ft_strncmp((*curr)->variable, name, len)
			&& (*curr)->variable[len] == '=')
		{
			tmp = *curr;
			*curr = (*curr)->next;
			free(tmp->variable);
			free(tmp);
			return ;
		}
		curr = &((*curr)->next);
	}
}

void	check_cmds(t_cmd *cmds)
{
	cmds->cmd_type = NONE;
	if (!cmds->args || !cmds->args[0])
		return ;
	if (!ft_strcmp("echo", cmds->args[0]))
		cmds->cmd_type = ECHO;
	if (!ft_strcmp("cd", cmds->args[0]))
		cmds->cmd_type = CD;
	if (!ft_strcmp("pwd", cmds->args[0]))
		cmds->cmd_type = PWD;
	if (!ft_strcmp("export", cmds->args[0]))
		cmds->cmd_type = EXPORT;
	if (!ft_strcmp("unset", cmds->args[0]))
		cmds->cmd_type = UNSET;
	if (!ft_strcmp("env", cmds->args[0]))
		cmds->cmd_type = ENV;
	if (!ft_strcmp("exit", cmds->args[0]))
		cmds->cmd_type = EXIT;
}