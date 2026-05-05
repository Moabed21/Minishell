/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:44:34 by moabed            #+#    #+#             */
/*   Updated: 2026/05/05 16:53:47 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executionpart.h"

void	apply_fd(int fd1, int fd)
{
	dup2(fd1, fd);
	close(fd1);
}

void	wait_child(t_exec *shell, t_cmd *node)
{
	int	status;

	waitpid(node->fork_id, &status, 0);
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->last_status = 128 + WTERMSIG(status);
		// if (WTERMSIG(status) == SIGINT)
		// 	write(1, "\n", 1);
		// else if (WTERMSIG(status) == SIGQUIT)
		// 	write(2, "Quit (core dumped)\n", 19);
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
			return ;
		}
	}
	else if (option == 2)
	{
		if (pipe(shell->fd) == -1)
		{
			node->fork_id = -1;
			shell->last_status = EXIT_FAILURE;
			return ;
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

void	execution(t_exec *shell)
{
	init_vals(shell, shell->cmds);
	if (shell->cmds_count == 1)
		execute_one_cmd(shell, shell->cmds);
	else
		multiple_cmds(shell, shell->cmds);
}
