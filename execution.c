/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:44:34 by moabed            #+#    #+#             */
/*   Updated: 2026/05/16 12:43:24 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/executionpart.h"

void	apply_fd(int fd1, int fd)
{
	if (fd1 == fd)
		return ;
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
		shell->last_status = 128 + WTERMSIG(status);
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

char	**findpath(t_env *env)
{
	int		i;
	char	**ev;
	char	*tmp;

	ev = NULL;
	while (env && !ev)
	{
		if (!ft_strcmp(env->key, "PATH"))
			ev = ft_split(env->value, ':');
		env = env->next;
	}
	i = -1;
	while (ev && ev[++i])
	{
		tmp = ft_strjoin(ev[i], "/");
		if (!tmp)
		{
			free2d_array(ev);
			return (NULL);
		}
		free(ev[i]);
		ev[i] = tmp;
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
