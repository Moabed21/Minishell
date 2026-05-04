/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:44:34 by moabed            #+#    #+#             */
/*   Updated: 2026/05/03 21:37:17 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executionpart.h"

void	wait_child(t_exec *shell, t_cmd *node)
{
	int	status;

	waitpid(node->fork_id, &status, 0);
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->last_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
	}
}

void	ft_fork_pipe(t_exec *shell, t_cmd *node, int option)
{
	if (option == 1)
	{
		node->fork_id = fork();
		if (node->fork_id == -1)
		{
			shell->last_status = EXIT_FAILURE;
			ruin_everything(shell);
		}
	}
	else if (option == 2)
	{
		if (pipe(shell->fd) == -1)
		{
			node->fork_id = -1;
			shell->last_status = EXIT_FAILURE;
			ruin_everything(shell);
		}
	}
}
char	**findpath(char **evar)
{
	int		i;
	char	**ev;
	char	*firstpart;

	i = -1;
	ev = NULL;
	while (evar[++i])
	{
		if (ft_strncmp(evar[i], "PATH=", 5) == 0)
		{
			ev = ft_split(evar[i] + 5, ':');
			break ;
		}
	}
	i = 0;
	if (!ev)
		return (NULL);
	while (ev[i])
	{
		firstpart = ft_strjoin(ev[i], "/");
		free(ev[i]);
		ev[i] = firstpart;
		i++;
	}
	return (ev);
}

void	multiple_cmds(t_exec *shell, t_cmd *cmds_list)
{
	ft_fork_pipe(shell, cmds_list, 2);
	if (!cmds_list)
		return ;
	while (cmds_list)
	{
		cmds_list = cmds_list->next;
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

void	init_vals(t_exec *shell, t_cmd *cmds)
{
	shell->cmds_count = 0;
	while (cmds)
	{
		check_cmds(cmds);
		cmds->fd_in = 0;
		cmds->fd_out = 1;
		shell->cmds_count++;
		cmds = cmds->next;
	}
}

void	execution(t_exec *shell)
{
	init_vals(shell, shell->cmds);
	if (shell->cmds_count == 1)
		execute_one_cmd(shell, shell->cmds);
	else
		multiple_cmds(shell, shell->cmds);
	shell->cmds = NULL;
}
